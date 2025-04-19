; Auto-generated. Do not edit!


(cl:in-package radar_msgs-msg)


;//! \htmlinclude Array.msg.html

(cl:defclass <Array> (roslisp-msg-protocol:ros-message)
  ((Array
    :reader Array
    :initarg :Array
    :type (cl:vector radar_msgs-msg:radar)
   :initform (cl:make-array 0 :element-type 'radar_msgs-msg:radar :initial-element (cl:make-instance 'radar_msgs-msg:radar))))
)

(cl:defclass Array (<Array>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Array>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Array)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name radar_msgs-msg:<Array> is deprecated: use radar_msgs-msg:Array instead.")))

(cl:ensure-generic-function 'Array-val :lambda-list '(m))
(cl:defmethod Array-val ((m <Array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader radar_msgs-msg:Array-val is deprecated.  Use radar_msgs-msg:Array instead.")
  (Array m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Array>) ostream)
  "Serializes a message object of type '<Array>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Array))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Array))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Array>) istream)
  "Deserializes a message object of type '<Array>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Array) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Array)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'radar_msgs-msg:radar))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Array>)))
  "Returns string type for a message object of type '<Array>"
  "radar_msgs/Array")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Array)))
  "Returns string type for a message object of type 'Array"
  "radar_msgs/Array")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Array>)))
  "Returns md5sum for a message object of type '<Array>"
  "997f34d9f4575d60cbee5bcd6077246d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Array)))
  "Returns md5sum for a message object of type 'Array"
  "997f34d9f4575d60cbee5bcd6077246d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Array>)))
  "Returns full string definition for message of type '<Array>"
  (cl:format cl:nil "radar[] Array~%================================================================================~%MSG: radar_msgs/radar~%int8 n~%float32 r~%float32 phi~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Array)))
  "Returns full string definition for message of type 'Array"
  (cl:format cl:nil "radar[] Array~%================================================================================~%MSG: radar_msgs/radar~%int8 n~%float32 r~%float32 phi~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Array>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Array) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Array>))
  "Converts a ROS message object to a list"
  (cl:list 'Array
    (cl:cons ':Array (Array msg))
))
