#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class CompressedCameraNode
{
public:
    CompressedCameraNode() : nh_("~"), it_(nh_)
    {
        // 获取参数
        nh_.param("device_id", device_id_, 0);
        nh_.param("frame_width", frame_width_, 640);
        nh_.param("frame_height", frame_height_, 480);
        nh_.param("fps", fps_, 30);
        nh_.param("jpeg_quality", jpeg_quality_, 95);
        
        // 创建压缩图像发布器
        compressed_pub_ = nh_.advertise<sensor_msgs::CompressedImage>("image_raw/compressed", 1);
        
        // 可选：同时发布原始图像（如果需要）
        // image_pub_ = it_.advertise("image_raw", 1);
        
        ROS_INFO("Starting USB camera with device ID: %d", device_id_);
        ROS_INFO("Resolution: %dx%d, FPS: %d, JPEG Quality: %d", 
                 frame_width_, frame_height_, fps_, jpeg_quality_);
    }
    
    bool initializeCamera()
    {
        // 打开相机
        cap_.open(device_id_);
        if (!cap_.isOpened())
        {
            ROS_ERROR("Failed to open USB camera with device ID: %d", device_id_);
            return false;
        }
        
        // 设置相机参数
        cap_.set(cv::CAP_PROP_FRAME_WIDTH, frame_width_);
        cap_.set(cv::CAP_PROP_FRAME_HEIGHT, frame_height_);
        cap_.set(cv::CAP_PROP_FPS, fps_);
        cap_.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
        
        return true;
    }
    
    void run()
    {
        cv::Mat frame;
        ros::Rate rate(fps_);
        
        // JPEG压缩参数
        std::vector<int> compression_params;
        compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression_params.push_back(jpeg_quality_);
        
        while (ros::ok())
        {
            if (!cap_.read(frame))
            {
                ROS_ERROR("Failed to read frame from camera");
                break;
            }
            
            if (frame.empty())
            {
                ROS_WARN("Empty frame received");
                continue;
            }
            
            // 创建压缩图像消息
            sensor_msgs::CompressedImage compressed_msg;
            compressed_msg.header.stamp = ros::Time::now();
            compressed_msg.header.frame_id = "camera_frame";
            compressed_msg.format = "jpeg";
            
            // 压缩图像
            if (cv::imencode(".jpg", frame, compressed_msg.data, compression_params))
            {
                compressed_pub_.publish(compressed_msg);
            }
            else
            {
                ROS_ERROR("Failed to compress image");
            }
            
            // 可选：同时发布原始图像
            /*
            sensor_msgs::ImagePtr image_msg = cv_bridge::CvImage(
                std_msgs::Header(), "bgr8", frame).toImageMsg();
            image_pub_.publish(image_msg);
            */
            
            ros::spinOnce();
            rate.sleep();
        }
        
        cap_.release();
    }
    
private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    cv::VideoCapture cap_;
    
    ros::Publisher compressed_pub_;
    image_transport::Publisher image_pub_;
    
    int device_id_;
    int frame_width_;
    int frame_height_;
    int fps_;
    int jpeg_quality_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_node");
    
    CompressedCameraNode camera_node;
    if (camera_node.initializeCamera())
    {
        camera_node.run();
    }
    else
    {
        ROS_ERROR("Failed to initialize camera");
        return 1;
    }
    
    return 0;
}