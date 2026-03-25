; Auto-generated. Do not edit!


(cl:in-package decision_making_pkg-srv)


;//! \htmlinclude StartTransport-request.msg.html

(cl:defclass <StartTransport-request> (roslisp-msg-protocol:ros-message)
  ((placement_type
    :reader placement_type
    :initarg :placement_type
    :type cl:fixnum
    :initform 0)
   (placement_spacing
    :reader placement_spacing
    :initarg :placement_spacing
    :type cl:float
    :initform 0.0)
   (start
    :reader start
    :initarg :start
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass StartTransport-request (<StartTransport-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StartTransport-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StartTransport-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decision_making_pkg-srv:<StartTransport-request> is deprecated: use decision_making_pkg-srv:StartTransport-request instead.")))

(cl:ensure-generic-function 'placement_type-val :lambda-list '(m))
(cl:defmethod placement_type-val ((m <StartTransport-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decision_making_pkg-srv:placement_type-val is deprecated.  Use decision_making_pkg-srv:placement_type instead.")
  (placement_type m))

(cl:ensure-generic-function 'placement_spacing-val :lambda-list '(m))
(cl:defmethod placement_spacing-val ((m <StartTransport-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decision_making_pkg-srv:placement_spacing-val is deprecated.  Use decision_making_pkg-srv:placement_spacing instead.")
  (placement_spacing m))

(cl:ensure-generic-function 'start-val :lambda-list '(m))
(cl:defmethod start-val ((m <StartTransport-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decision_making_pkg-srv:start-val is deprecated.  Use decision_making_pkg-srv:start instead.")
  (start m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StartTransport-request>) ostream)
  "Serializes a message object of type '<StartTransport-request>"
  (cl:let* ((signed (cl:slot-value msg 'placement_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'placement_spacing))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'start) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StartTransport-request>) istream)
  "Deserializes a message object of type '<StartTransport-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'placement_type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'placement_spacing) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'start) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StartTransport-request>)))
  "Returns string type for a service object of type '<StartTransport-request>"
  "decision_making_pkg/StartTransportRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StartTransport-request)))
  "Returns string type for a service object of type 'StartTransport-request"
  "decision_making_pkg/StartTransportRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StartTransport-request>)))
  "Returns md5sum for a message object of type '<StartTransport-request>"
  "a29e616be9ef3884c858e9b72ec65988")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StartTransport-request)))
  "Returns md5sum for a message object of type 'StartTransport-request"
  "a29e616be9ef3884c858e9b72ec65988")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StartTransport-request>)))
  "Returns full string definition for message of type '<StartTransport-request>"
  (cl:format cl:nil "# 请求部分~%int8 placement_type      # 0=网格摆放, 1=三角错位摆放~%float32 placement_spacing # 摆放间距（米）~%bool start               # 开始标志~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StartTransport-request)))
  "Returns full string definition for message of type 'StartTransport-request"
  (cl:format cl:nil "# 请求部分~%int8 placement_type      # 0=网格摆放, 1=三角错位摆放~%float32 placement_spacing # 摆放间距（米）~%bool start               # 开始标志~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StartTransport-request>))
  (cl:+ 0
     1
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StartTransport-request>))
  "Converts a ROS message object to a list"
  (cl:list 'StartTransport-request
    (cl:cons ':placement_type (placement_type msg))
    (cl:cons ':placement_spacing (placement_spacing msg))
    (cl:cons ':start (start msg))
))
;//! \htmlinclude StartTransport-response.msg.html

(cl:defclass <StartTransport-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass StartTransport-response (<StartTransport-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StartTransport-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StartTransport-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decision_making_pkg-srv:<StartTransport-response> is deprecated: use decision_making_pkg-srv:StartTransport-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <StartTransport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decision_making_pkg-srv:success-val is deprecated.  Use decision_making_pkg-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <StartTransport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decision_making_pkg-srv:message-val is deprecated.  Use decision_making_pkg-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StartTransport-response>) ostream)
  "Serializes a message object of type '<StartTransport-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StartTransport-response>) istream)
  "Deserializes a message object of type '<StartTransport-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StartTransport-response>)))
  "Returns string type for a service object of type '<StartTransport-response>"
  "decision_making_pkg/StartTransportResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StartTransport-response)))
  "Returns string type for a service object of type 'StartTransport-response"
  "decision_making_pkg/StartTransportResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StartTransport-response>)))
  "Returns md5sum for a message object of type '<StartTransport-response>"
  "a29e616be9ef3884c858e9b72ec65988")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StartTransport-response)))
  "Returns md5sum for a message object of type 'StartTransport-response"
  "a29e616be9ef3884c858e9b72ec65988")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StartTransport-response>)))
  "Returns full string definition for message of type '<StartTransport-response>"
  (cl:format cl:nil "# 响应部分~%bool success~%string message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StartTransport-response)))
  "Returns full string definition for message of type 'StartTransport-response"
  (cl:format cl:nil "# 响应部分~%bool success~%string message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StartTransport-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StartTransport-response>))
  "Converts a ROS message object to a list"
  (cl:list 'StartTransport-response
    (cl:cons ':success (success msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'StartTransport)))
  'StartTransport-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'StartTransport)))
  'StartTransport-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StartTransport)))
  "Returns string type for a service object of type '<StartTransport>"
  "decision_making_pkg/StartTransport")