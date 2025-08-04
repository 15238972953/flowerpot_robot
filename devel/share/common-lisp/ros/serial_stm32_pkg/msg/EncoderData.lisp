; Auto-generated. Do not edit!


(cl:in-package serial_stm32_pkg-msg)


;//! \htmlinclude EncoderData.msg.html

(cl:defclass <EncoderData> (roslisp-msg-protocol:ros-message)
  ((Encoder_Left
    :reader Encoder_Left
    :initarg :Encoder_Left
    :type cl:integer
    :initform 0)
   (Encoder_Right
    :reader Encoder_Right
    :initarg :Encoder_Right
    :type cl:integer
    :initform 0))
)

(cl:defclass EncoderData (<EncoderData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EncoderData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EncoderData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name serial_stm32_pkg-msg:<EncoderData> is deprecated: use serial_stm32_pkg-msg:EncoderData instead.")))

(cl:ensure-generic-function 'Encoder_Left-val :lambda-list '(m))
(cl:defmethod Encoder_Left-val ((m <EncoderData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_stm32_pkg-msg:Encoder_Left-val is deprecated.  Use serial_stm32_pkg-msg:Encoder_Left instead.")
  (Encoder_Left m))

(cl:ensure-generic-function 'Encoder_Right-val :lambda-list '(m))
(cl:defmethod Encoder_Right-val ((m <EncoderData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_stm32_pkg-msg:Encoder_Right-val is deprecated.  Use serial_stm32_pkg-msg:Encoder_Right instead.")
  (Encoder_Right m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EncoderData>) ostream)
  "Serializes a message object of type '<EncoderData>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Encoder_Left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Encoder_Left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'Encoder_Left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'Encoder_Left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Encoder_Right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Encoder_Right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'Encoder_Right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'Encoder_Right)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EncoderData>) istream)
  "Deserializes a message object of type '<EncoderData>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Encoder_Left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Encoder_Left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'Encoder_Left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'Encoder_Left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Encoder_Right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'Encoder_Right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'Encoder_Right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'Encoder_Right)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EncoderData>)))
  "Returns string type for a message object of type '<EncoderData>"
  "serial_stm32_pkg/EncoderData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EncoderData)))
  "Returns string type for a message object of type 'EncoderData"
  "serial_stm32_pkg/EncoderData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EncoderData>)))
  "Returns md5sum for a message object of type '<EncoderData>"
  "4f445708b5fc7868c7f94d572914b055")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EncoderData)))
  "Returns md5sum for a message object of type 'EncoderData"
  "4f445708b5fc7868c7f94d572914b055")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EncoderData>)))
  "Returns full string definition for message of type '<EncoderData>"
  (cl:format cl:nil "uint32 Encoder_Left~%uint32 Encoder_Right~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EncoderData)))
  "Returns full string definition for message of type 'EncoderData"
  (cl:format cl:nil "uint32 Encoder_Left~%uint32 Encoder_Right~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EncoderData>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EncoderData>))
  "Converts a ROS message object to a list"
  (cl:list 'EncoderData
    (cl:cons ':Encoder_Left (Encoder_Left msg))
    (cl:cons ':Encoder_Right (Encoder_Right msg))
))
