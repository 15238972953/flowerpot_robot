; Auto-generated. Do not edit!


(cl:in-package common_msgs_pkg-msg)


;//! \htmlinclude encoder.msg.html

(cl:defclass <encoder> (roslisp-msg-protocol:ros-message)
  ((right_speed
    :reader right_speed
    :initarg :right_speed
    :type cl:float
    :initform 0.0)
   (left_speed
    :reader left_speed
    :initarg :left_speed
    :type cl:float
    :initform 0.0))
)

(cl:defclass encoder (<encoder>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <encoder>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'encoder)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name common_msgs_pkg-msg:<encoder> is deprecated: use common_msgs_pkg-msg:encoder instead.")))

(cl:ensure-generic-function 'right_speed-val :lambda-list '(m))
(cl:defmethod right_speed-val ((m <encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader common_msgs_pkg-msg:right_speed-val is deprecated.  Use common_msgs_pkg-msg:right_speed instead.")
  (right_speed m))

(cl:ensure-generic-function 'left_speed-val :lambda-list '(m))
(cl:defmethod left_speed-val ((m <encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader common_msgs_pkg-msg:left_speed-val is deprecated.  Use common_msgs_pkg-msg:left_speed instead.")
  (left_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <encoder>) ostream)
  "Serializes a message object of type '<encoder>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'right_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'left_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <encoder>) istream)
  "Deserializes a message object of type '<encoder>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'right_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left_speed) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<encoder>)))
  "Returns string type for a message object of type '<encoder>"
  "common_msgs_pkg/encoder")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'encoder)))
  "Returns string type for a message object of type 'encoder"
  "common_msgs_pkg/encoder")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<encoder>)))
  "Returns md5sum for a message object of type '<encoder>"
  "25f978d6cccf487431c99e3026d97330")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'encoder)))
  "Returns md5sum for a message object of type 'encoder"
  "25f978d6cccf487431c99e3026d97330")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<encoder>)))
  "Returns full string definition for message of type '<encoder>"
  (cl:format cl:nil "float32 right_speed~%float32 left_speed~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'encoder)))
  "Returns full string definition for message of type 'encoder"
  (cl:format cl:nil "float32 right_speed~%float32 left_speed~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <encoder>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <encoder>))
  "Converts a ROS message object to a list"
  (cl:list 'encoder
    (cl:cons ':right_speed (right_speed msg))
    (cl:cons ':left_speed (left_speed msg))
))
