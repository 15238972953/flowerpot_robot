;; Auto-generated. Do not edit!


(when (boundp 'radar_msgs::array)
  (if (not (find-package "RADAR_MSGS"))
    (make-package "RADAR_MSGS"))
  (shadow 'array (find-package "RADAR_MSGS")))
(unless (find-package "RADAR_MSGS::ARRAY")
  (make-package "RADAR_MSGS::ARRAY"))

(in-package "ROS")
;;//! \htmlinclude array.msg.html


(defclass radar_msgs::array
  :super ros::object
  :slots (_array ))

(defmethod radar_msgs::array
  (:init
   (&key
    ((:array __array) ())
    )
   (send-super :init)
   (setq _array __array)
   self)
  (:array
   (&rest __array)
   (if (keywordp (car __array))
       (send* _array __array)
     (progn
       (if __array (setq _array (car __array)))
       _array)))
  (:serialization-length
   ()
   (+
    ;; radar_msgs/radar[] _array
    (apply #'+ (send-all _array :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; radar_msgs/radar[] _array
     (write-long (length _array) s)
     (dolist (elem _array)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; radar_msgs/radar[] _array
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _array (let (r) (dotimes (i n) (push (instance radar_msgs::radar :init) r)) r))
     (dolist (elem- _array)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get radar_msgs::array :md5sum-) "6a3b08d0414549cec20d43547def240d")
(setf (get radar_msgs::array :datatype-) "radar_msgs/array")
(setf (get radar_msgs::array :definition-)
      "radar[] array
================================================================================
MSG: radar_msgs/radar
int8 n
float32 r
float32 phi
")



(provide :radar_msgs/array "6a3b08d0414549cec20d43547def240d")


