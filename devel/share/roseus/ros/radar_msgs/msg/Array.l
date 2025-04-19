;; Auto-generated. Do not edit!


(when (boundp 'radar_msgs::Array)
  (if (not (find-package "RADAR_MSGS"))
    (make-package "RADAR_MSGS"))
  (shadow 'Array (find-package "RADAR_MSGS")))
(unless (find-package "RADAR_MSGS::ARRAY")
  (make-package "RADAR_MSGS::ARRAY"))

(in-package "ROS")
;;//! \htmlinclude Array.msg.html


(defclass radar_msgs::Array
  :super ros::object
  :slots (_Array ))

(defmethod radar_msgs::Array
  (:init
   (&key
    ((:Array __Array) ())
    )
   (send-super :init)
   (setq _Array __Array)
   self)
  (:Array
   (&rest __Array)
   (if (keywordp (car __Array))
       (send* _Array __Array)
     (progn
       (if __Array (setq _Array (car __Array)))
       _Array)))
  (:serialization-length
   ()
   (+
    ;; radar_msgs/radar[] _Array
    (apply #'+ (send-all _Array :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; radar_msgs/radar[] _Array
     (write-long (length _Array) s)
     (dolist (elem _Array)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; radar_msgs/radar[] _Array
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Array (let (r) (dotimes (i n) (push (instance radar_msgs::radar :init) r)) r))
     (dolist (elem- _Array)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get radar_msgs::Array :md5sum-) "997f34d9f4575d60cbee5bcd6077246d")
(setf (get radar_msgs::Array :datatype-) "radar_msgs/Array")
(setf (get radar_msgs::Array :definition-)
      "radar[] Array
================================================================================
MSG: radar_msgs/radar
int8 n
float32 r
float32 phi
")



(provide :radar_msgs/Array "997f34d9f4575d60cbee5bcd6077246d")


