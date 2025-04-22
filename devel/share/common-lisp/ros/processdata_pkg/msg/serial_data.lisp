; Auto-generated. Do not edit!


(cl:in-package processdata_pkg-msg)


;//! \htmlinclude serial_data.msg.html

(cl:defclass <serial_data> (roslisp-msg-protocol:ros-message)
  ((PWM_Left
    :reader PWM_Left
    :initarg :PWM_Left
    :type cl:fixnum
    :initform 0)
   (PWM_Right
    :reader PWM_Right
    :initarg :PWM_Right
    :type cl:fixnum
    :initform 0)
   (command
    :reader command
    :initarg :command
    :type cl:fixnum
    :initform 0))
)

(cl:defclass serial_data (<serial_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <serial_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'serial_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name processdata_pkg-msg:<serial_data> is deprecated: use processdata_pkg-msg:serial_data instead.")))

(cl:ensure-generic-function 'PWM_Left-val :lambda-list '(m))
(cl:defmethod PWM_Left-val ((m <serial_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader processdata_pkg-msg:PWM_Left-val is deprecated.  Use processdata_pkg-msg:PWM_Left instead.")
  (PWM_Left m))

(cl:ensure-generic-function 'PWM_Right-val :lambda-list '(m))
(cl:defmethod PWM_Right-val ((m <serial_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader processdata_pkg-msg:PWM_Right-val is deprecated.  Use processdata_pkg-msg:PWM_Right instead.")
  (PWM_Right m))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <serial_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader processdata_pkg-msg:command-val is deprecated.  Use processdata_pkg-msg:command instead.")
  (command m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <serial_data>) ostream)
  "Serializes a message object of type '<serial_data>"
  (cl:let* ((signed (cl:slot-value msg 'PWM_Left)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'PWM_Right)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'command)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <serial_data>) istream)
  "Deserializes a message object of type '<serial_data>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'PWM_Left) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'PWM_Right) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<serial_data>)))
  "Returns string type for a message object of type '<serial_data>"
  "processdata_pkg/serial_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serial_data)))
  "Returns string type for a message object of type 'serial_data"
  "processdata_pkg/serial_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<serial_data>)))
  "Returns md5sum for a message object of type '<serial_data>"
  "55d8902ce6b1a26e186815e49dac35e0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'serial_data)))
  "Returns md5sum for a message object of type 'serial_data"
  "55d8902ce6b1a26e186815e49dac35e0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<serial_data>)))
  "Returns full string definition for message of type '<serial_data>"
  (cl:format cl:nil "int8 PWM_Left~%int8 PWM_Right~%int8 command~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'serial_data)))
  "Returns full string definition for message of type 'serial_data"
  (cl:format cl:nil "int8 PWM_Left~%int8 PWM_Right~%int8 command~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <serial_data>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <serial_data>))
  "Converts a ROS message object to a list"
  (cl:list 'serial_data
    (cl:cons ':PWM_Left (PWM_Left msg))
    (cl:cons ':PWM_Right (PWM_Right msg))
    (cl:cons ':command (command msg))
))
