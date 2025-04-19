; Auto-generated. Do not edit!


(cl:in-package yolo11_pkg-msg)


;//! \htmlinclude array.msg.html

(cl:defclass <array> (roslisp-msg-protocol:ros-message)
  ((array
    :reader array
    :initarg :array
    :type (cl:vector yolo11_pkg-msg:coordinate)
   :initform (cl:make-array 0 :element-type 'yolo11_pkg-msg:coordinate :initial-element (cl:make-instance 'yolo11_pkg-msg:coordinate))))
)

(cl:defclass array (<array>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <array>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'array)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name yolo11_pkg-msg:<array> is deprecated: use yolo11_pkg-msg:array instead.")))

(cl:ensure-generic-function 'array-val :lambda-list '(m))
(cl:defmethod array-val ((m <array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader yolo11_pkg-msg:array-val is deprecated.  Use yolo11_pkg-msg:array instead.")
  (array m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <array>) ostream)
  "Serializes a message object of type '<array>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'array))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'array))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <array>) istream)
  "Deserializes a message object of type '<array>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'array) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'array)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'yolo11_pkg-msg:coordinate))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<array>)))
  "Returns string type for a message object of type '<array>"
  "yolo11_pkg/array")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'array)))
  "Returns string type for a message object of type 'array"
  "yolo11_pkg/array")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<array>)))
  "Returns md5sum for a message object of type '<array>"
  "5a32149513fa1aa3cce229c0f0ef79c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'array)))
  "Returns md5sum for a message object of type 'array"
  "5a32149513fa1aa3cce229c0f0ef79c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<array>)))
  "Returns full string definition for message of type '<array>"
  (cl:format cl:nil "coordinate[] array~%================================================================================~%MSG: yolo11_pkg/coordinate~%int16 x~%int16 y~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'array)))
  "Returns full string definition for message of type 'array"
  (cl:format cl:nil "coordinate[] array~%================================================================================~%MSG: yolo11_pkg/coordinate~%int16 x~%int16 y~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <array>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'array) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <array>))
  "Converts a ROS message object to a list"
  (cl:list 'array
    (cl:cons ':array (array msg))
))
