#!/home/jetson/miniconda3/envs/yolo11/bin/python

import argparse
import cv2
import numpy as np
import onnxruntime as ort
import yaml
import time
from yolo11_pkg.msg import coordinate, array
import rospy
from Coordinate_Transformation import pixel_to_world
# from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import threading
from sensor_msgs.msg import CompressedImage

class YOLOv8:
    """YOLOv8 object detection model class for handling inference and visualization."""

    def __init__(self, onnx_model, yaml_file, confidence_thres, iou_thres):
        """
        Initializes an instance of the YOLOv8 class.
        """
        self.confidence_thres = confidence_thres
        self.iou_thres = iou_thres

        # Load COCO classes
        with open(yaml_file, "r", encoding="utf-8") as f:
            self.classes = yaml.safe_load(f)["names"]

        # Generate color palette
        self.color_palette = np.random.randint(0, 255, size=(len(self.classes), 3), dtype=np.uint8)

        # ONNX Runtime session with optimization
        session_options = ort.SessionOptions()
        session_options.graph_optimization_level = ort.GraphOptimizationLevel.ORT_ENABLE_ALL
        self.session = ort.InferenceSession(onnx_model, sess_options=session_options,
                                            providers=["CUDAExecutionProvider", "CPUExecutionProvider"])

        # Get input shape
        model_inputs = self.session.get_inputs()
        self.input_name = model_inputs[0].name
        self.input_shape = model_inputs[0].shape
        self.input_width, self.input_height = self.input_shape[2], self.input_shape[3]

        # ROS initialization
        rospy.init_node("yolo11_node")
        self.yolo11_pub = rospy.Publisher("yolo11_data", array, queue_size=30)
        
        # CV bridge for converting ROS Image messages to OpenCV images
        self.bridge = CvBridge()
        
        # Subscribe to camera topic
        # 根据你的实际相机话题修改这里，常见的有：
        # "/camera/image_raw", "/usb_cam/image_raw", "/camera/color/image_raw"
        # self.image_sub = rospy.Subscriber("/camera/image_raw", Image, self.image_callback)
        self.image_sub = rospy.Subscriber("/camera_node/image_raw/compressed", CompressedImage, self.image_callback)

        # Store the latest frame
        self.latest_frame = None
        self.frame_lock = threading.Lock()
        
        # FPS calculation
        self.frame_count = 0
        self.start_time = time.time()

    def image_callback(self, msg):
        """Callback for processing incoming compressed ROS image messages."""
        try:
            # 将压缩图像数据转换为numpy数组
            np_arr = np.frombuffer(msg.data, np.uint8)
            
            # 使用OpenCV解码JPEG图像
            cv_image = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
            
            if cv_image is not None:
                # Store the latest frame
                with self.frame_lock:
                    self.latest_frame = cv_image
            else:
                rospy.logwarn("Failed to decode compressed image")
                
        except Exception as e:
            rospy.logerr("Compressed image processing error: %s", e)

    def draw_detections(self, img, box, score, class_id):
        """Draws bounding boxes and labels."""
        x1, y1, w, h = box
        color = self.color_palette[class_id].tolist()
        label = f"{self.classes[class_id]}: {score:.2f}"

        # Draw rectangle and label background
        cv2.rectangle(img, (x1, y1), (x1 + w, y1 + h), color, 2)
        (label_width, label_height), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
        label_y = max(y1, label_height + 5)
        cv2.rectangle(img, (x1, label_y - label_height), (x1 + label_width, label_y), color, cv2.FILLED)

        # Put label text
        cv2.putText(img, label, (x1, label_y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, cv2.LINE_AA)

    def preprocess(self, img):
        """Preprocess the input image."""
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = cv2.resize(img, (self.input_width, self.input_height))
        img = img.astype(np.float16) / 255.0
        img = np.transpose(img, (2, 0, 1))  # Channel first
        return np.expand_dims(img, axis=0)

    def postprocess(self, input_image, output):
        """Extracts bounding boxes, scores, and class IDs."""
        outputs = np.squeeze(output[0]).T
        img_h, img_w = input_image.shape[:2]
        scale_w, scale_h = img_w / self.input_width, img_h / self.input_height

        # Extract scores, boxes, and class ids
        scores = np.max(outputs[:, 4:], axis=1)
        valid_indices = np.where(scores >= self.confidence_thres)[0]
        class_ids = np.argmax(outputs[valid_indices, 4:], axis=1)
        boxes = outputs[valid_indices, :4]

        # Convert to absolute coordinates
        boxes[:, 0] = (boxes[:, 0] - boxes[:, 2] / 2) * scale_w
        boxes[:, 1] = (boxes[:, 1] - boxes[:, 3] / 2) * scale_h
        boxes[:, 2] *= scale_w
        boxes[:, 3] *= scale_h
        boxes = boxes.astype(int)

        # Apply NMS
        indices = cv2.dnn.NMSBoxes(boxes.tolist(), scores[valid_indices].tolist(),
                                   self.confidence_thres, self.iou_thres)
        
        msg = array()
        if len(indices) > 0:
            for i in indices.flatten():
                self.draw_detections(input_image, boxes[i], scores[valid_indices[i]], class_ids[i])
                pot_coordinate = coordinate()
                pot_coordinate.x = int(boxes[i][0] + boxes[i][2] / 2)
                pot_coordinate.y = int(boxes[i][1] + boxes[i][3])
                pot_coordinate.x, pot_coordinate.y = pixel_to_world(pot_coordinate.x / 2, pot_coordinate.y / 2)
                msg.array.append(pot_coordinate)
        self.yolo11_pub.publish(msg)
        rospy.loginfo("yolo11_data:%s", msg)

        return input_image

    def process_frame(self, frame):
        """Processes a single frame."""
        img_data = self.preprocess(frame)

        start_time = time.time()
        output = self.session.run(None, {self.input_name: img_data})
        inference_time = time.time() - start_time
        
        # Calculate FPS
        self.frame_count += 1
        elapsed_time = time.time() - self.start_time
        if elapsed_time > 1.0:  # Update FPS every second
            fps = self.frame_count / elapsed_time
            rospy.loginfo("[INFO] YOLO FPS: %.2f, Inference time: %.3fs", fps, inference_time)
            self.frame_count = 0
            self.start_time = time.time()

        return self.postprocess(frame.copy(), output)

    def run_ros_detection(self):
        """Runs object detection on ROS image topics."""
        cv2.namedWindow("YOLOv8 Real-time Detection", cv2.WINDOW_NORMAL)
        rospy.loginfo("YOLOv8 node started. Waiting for images...")

        rate = rospy.Rate(30)  # 30 Hz

        while not rospy.is_shutdown():
            # Get the latest frame
            with self.frame_lock:
                if self.latest_frame is not None:
                    frame = self.latest_frame.copy()
                else:
                    frame = None

            if frame is not None:
                try:
                    processed_frame = self.process_frame(frame)
                    cv2.imshow("YOLOv8 Real-time Detection", processed_frame)
                    
                    # Check for quit key
                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        break
                        
                except Exception as e:
                    rospy.logerr("Error processing frame: %s", e)

            rate.sleep()

        cv2.destroyAllWindows()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--model", type=str, default="/home/jetson/catkin_ws/src/yolo11_pkg/scripts/best_fp16.onnx", help="Path to ONNX model.")
    parser.add_argument("--yaml", default="/home/jetson/catkin_ws/src/yolo11_pkg/scripts/flower.yaml", help="Path to YAML file containing class names.")
    parser.add_argument("--conf-thres", type=float, default=0.8, help="Confidence threshold")
    parser.add_argument("--iou-thres", type=float, default=0.7, help="NMS IoU threshold")
    
    # args = parser.parse_args()
    args, unknown = parser.parse_known_args()

    detector = YOLOv8(args.model, args.yaml, args.conf_thres, args.iou_thres)
    detector.run_ros_detection()