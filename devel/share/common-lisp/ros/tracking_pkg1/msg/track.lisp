; Auto-generated. Do not edit!


(cl:in-package tracking_pkg1-msg)


;//! \htmlinclude track.msg.html

(cl:defclass <track> (roslisp-msg-protocol:ros-message)
  ((line
    :reader line
    :initarg :line
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 4 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass track (<track>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <track>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'track)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name tracking_pkg1-msg:<track> is deprecated: use tracking_pkg1-msg:track instead.")))

(cl:ensure-generic-function 'line-val :lambda-list '(m))
(cl:defmethod line-val ((m <track>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tracking_pkg1-msg:line-val is deprecated.  Use tracking_pkg1-msg:line instead.")
  (line m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <track>) ostream)
  "Serializes a message object of type '<track>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'line))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <track>) istream)
  "Deserializes a message object of type '<track>"
  (cl:setf (cl:slot-value msg 'line) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'line)))
    (cl:dotimes (i 4)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<track>)))
  "Returns string type for a message object of type '<track>"
  "tracking_pkg1/track")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'track)))
  "Returns string type for a message object of type 'track"
  "tracking_pkg1/track")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<track>)))
  "Returns md5sum for a message object of type '<track>"
  "6d30351f4c1b67d57e1e20725088b7c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'track)))
  "Returns md5sum for a message object of type 'track"
  "6d30351f4c1b67d57e1e20725088b7c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<track>)))
  "Returns full string definition for message of type '<track>"
  (cl:format cl:nil "int16[4] line~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'track)))
  "Returns full string definition for message of type 'track"
  (cl:format cl:nil "int16[4] line~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <track>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'line) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <track>))
  "Converts a ROS message object to a list"
  (cl:list 'track
    (cl:cons ':line (line msg))
))
