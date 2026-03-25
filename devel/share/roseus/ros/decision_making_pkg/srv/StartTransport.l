;; Auto-generated. Do not edit!


(when (boundp 'decision_making_pkg::StartTransport)
  (if (not (find-package "DECISION_MAKING_PKG"))
    (make-package "DECISION_MAKING_PKG"))
  (shadow 'StartTransport (find-package "DECISION_MAKING_PKG")))
(unless (find-package "DECISION_MAKING_PKG::STARTTRANSPORT")
  (make-package "DECISION_MAKING_PKG::STARTTRANSPORT"))
(unless (find-package "DECISION_MAKING_PKG::STARTTRANSPORTREQUEST")
  (make-package "DECISION_MAKING_PKG::STARTTRANSPORTREQUEST"))
(unless (find-package "DECISION_MAKING_PKG::STARTTRANSPORTRESPONSE")
  (make-package "DECISION_MAKING_PKG::STARTTRANSPORTRESPONSE"))

(in-package "ROS")





(defclass decision_making_pkg::StartTransportRequest
  :super ros::object
  :slots (_placement_type _placement_spacing _start ))

(defmethod decision_making_pkg::StartTransportRequest
  (:init
   (&key
    ((:placement_type __placement_type) 0)
    ((:placement_spacing __placement_spacing) 0.0)
    ((:start __start) nil)
    )
   (send-super :init)
   (setq _placement_type (round __placement_type))
   (setq _placement_spacing (float __placement_spacing))
   (setq _start __start)
   self)
  (:placement_type
   (&optional __placement_type)
   (if __placement_type (setq _placement_type __placement_type)) _placement_type)
  (:placement_spacing
   (&optional __placement_spacing)
   (if __placement_spacing (setq _placement_spacing __placement_spacing)) _placement_spacing)
  (:start
   (&optional (__start :null))
   (if (not (eq __start :null)) (setq _start __start)) _start)
  (:serialization-length
   ()
   (+
    ;; int8 _placement_type
    1
    ;; float32 _placement_spacing
    4
    ;; bool _start
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _placement_type
       (write-byte _placement_type s)
     ;; float32 _placement_spacing
       (sys::poke _placement_spacing (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _start
       (if _start (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _placement_type
     (setq _placement_type (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _placement_type 127) (setq _placement_type (- _placement_type 256)))
   ;; float32 _placement_spacing
     (setq _placement_spacing (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _start
     (setq _start (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass decision_making_pkg::StartTransportResponse
  :super ros::object
  :slots (_success _message ))

(defmethod decision_making_pkg::StartTransportResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _message (string __message))
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass decision_making_pkg::StartTransport
  :super ros::object
  :slots ())

(setf (get decision_making_pkg::StartTransport :md5sum-) "a29e616be9ef3884c858e9b72ec65988")
(setf (get decision_making_pkg::StartTransport :datatype-) "decision_making_pkg/StartTransport")
(setf (get decision_making_pkg::StartTransport :request) decision_making_pkg::StartTransportRequest)
(setf (get decision_making_pkg::StartTransport :response) decision_making_pkg::StartTransportResponse)

(defmethod decision_making_pkg::StartTransportRequest
  (:response () (instance decision_making_pkg::StartTransportResponse :init)))

(setf (get decision_making_pkg::StartTransportRequest :md5sum-) "a29e616be9ef3884c858e9b72ec65988")
(setf (get decision_making_pkg::StartTransportRequest :datatype-) "decision_making_pkg/StartTransportRequest")
(setf (get decision_making_pkg::StartTransportRequest :definition-)
      "# 请求部分
int8 placement_type      # 0=网格摆放, 1=三角错位摆放
float32 placement_spacing # 摆放间距（米）
bool start               # 开始标志
---
# 响应部分
bool success
string message
")

(setf (get decision_making_pkg::StartTransportResponse :md5sum-) "a29e616be9ef3884c858e9b72ec65988")
(setf (get decision_making_pkg::StartTransportResponse :datatype-) "decision_making_pkg/StartTransportResponse")
(setf (get decision_making_pkg::StartTransportResponse :definition-)
      "# 请求部分
int8 placement_type      # 0=网格摆放, 1=三角错位摆放
float32 placement_spacing # 摆放间距（米）
bool start               # 开始标志
---
# 响应部分
bool success
string message
")



(provide :decision_making_pkg/StartTransport "a29e616be9ef3884c858e9b72ec65988")


