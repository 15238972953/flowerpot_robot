; Auto-generated. Do not edit!


(cl:in-package radar_msgs-msg)


;//! \htmlinclude radar.msg.html

(cl:defclass <radar> (roslisp-msg-protocol:ros-message)
  ((n
    :reader n
    :initarg :n
    :type cl:fixnum
    :initform 0)
   (r
    :reader r
    :initarg :r
    :type cl:float
    :initform 0.0)
   (phi
    :reader phi
    :initarg :phi
    :type cl:float
    :initform 0.0))
)

(cl:defclass radar (<radar>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <radar>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'radar)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name radar_msgs-msg:<radar> is deprecated: use radar_msgs-msg:radar instead.")))

(cl:ensure-generic-function 'n-val :lambda-list '(m))
(cl:defmethod n-val ((m <radar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader radar_msgs-msg:n-val is deprecated.  Use radar_msgs-msg:n instead.")
  (n m))

(cl:ensure-generic-function 'r-val :lambda-list '(m))
(cl:defmethod r-val ((m <radar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader radar_msgs-msg:r-val is deprecated.  Use radar_msgs-msg:r instead.")
  (r m))

(cl:ensure-generic-function 'phi-val :lambda-list '(m))
(cl:defmethod phi-val ((m <radar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader radar_msgs-msg:phi-val is deprecated.  Use radar_msgs-msg:phi instead.")
  (phi m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <radar>) ostream)
  "Serializes a message object of type '<radar>"
  (cl:let* ((signed (cl:slot-value msg 'n)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'r))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'phi))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <radar>) istream)
  "Deserializes a message object of type '<radar>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'r) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'phi) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<radar>)))
  "Returns string type for a message object of type '<radar>"
  "radar_msgs/radar")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'radar)))
  "Returns string type for a message object of type 'radar"
  "radar_msgs/radar")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<radar>)))
  "Returns md5sum for a message object of type '<radar>"
  "b3a8cc87ce2d38b8fa7a080b864bbe8e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'radar)))
  "Returns md5sum for a message object of type 'radar"
  "b3a8cc87ce2d38b8fa7a080b864bbe8e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<radar>)))
  "Returns full string definition for message of type '<radar>"
  (cl:format cl:nil "int8 n~%float32 r~%float32 phi~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'radar)))
  "Returns full string definition for message of type 'radar"
  (cl:format cl:nil "int8 n~%float32 r~%float32 phi~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <radar>))
  (cl:+ 0
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <radar>))
  "Converts a ROS message object to a list"
  (cl:list 'radar
    (cl:cons ':n (n msg))
    (cl:cons ':r (r msg))
    (cl:cons ':phi (phi msg))
))
