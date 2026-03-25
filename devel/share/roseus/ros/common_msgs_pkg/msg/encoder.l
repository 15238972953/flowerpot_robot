;; Auto-generated. Do not edit!


(when (boundp 'common_msgs_pkg::encoder)
  (if (not (find-package "COMMON_MSGS_PKG"))
    (make-package "COMMON_MSGS_PKG"))
  (shadow 'encoder (find-package "COMMON_MSGS_PKG")))
(unless (find-package "COMMON_MSGS_PKG::ENCODER")
  (make-package "COMMON_MSGS_PKG::ENCODER"))

(in-package "ROS")
;;//! \htmlinclude encoder.msg.html


(defclass common_msgs_pkg::encoder
  :super ros::object
  :slots (_right_speed _left_speed ))

(defmethod common_msgs_pkg::encoder
  (:init
   (&key
    ((:right_speed __right_speed) 0.0)
    ((:left_speed __left_speed) 0.0)
    )
   (send-super :init)
   (setq _right_speed (float __right_speed))
   (setq _left_speed (float __left_speed))
   self)
  (:right_speed
   (&optional __right_speed)
   (if __right_speed (setq _right_speed __right_speed)) _right_speed)
  (:left_speed
   (&optional __left_speed)
   (if __left_speed (setq _left_speed __left_speed)) _left_speed)
  (:serialization-length
   ()
   (+
    ;; float32 _right_speed
    4
    ;; float32 _left_speed
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _right_speed
       (sys::poke _right_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _left_speed
       (sys::poke _left_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _right_speed
     (setq _right_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _left_speed
     (setq _left_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get common_msgs_pkg::encoder :md5sum-) "25f978d6cccf487431c99e3026d97330")
(setf (get common_msgs_pkg::encoder :datatype-) "common_msgs_pkg/encoder")
(setf (get common_msgs_pkg::encoder :definition-)
      "float32 right_speed
float32 left_speed
")



(provide :common_msgs_pkg/encoder "25f978d6cccf487431c99e3026d97330")


