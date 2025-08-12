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
  :slots (_right_distance _left_distance ))

(defmethod common_msgs_pkg::encoder
  (:init
   (&key
    ((:right_distance __right_distance) 0.0)
    ((:left_distance __left_distance) 0.0)
    )
   (send-super :init)
   (setq _right_distance (float __right_distance))
   (setq _left_distance (float __left_distance))
   self)
  (:right_distance
   (&optional __right_distance)
   (if __right_distance (setq _right_distance __right_distance)) _right_distance)
  (:left_distance
   (&optional __left_distance)
   (if __left_distance (setq _left_distance __left_distance)) _left_distance)
  (:serialization-length
   ()
   (+
    ;; float32 _right_distance
    4
    ;; float32 _left_distance
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _right_distance
       (sys::poke _right_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _left_distance
       (sys::poke _left_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _right_distance
     (setq _right_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _left_distance
     (setq _left_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get common_msgs_pkg::encoder :md5sum-) "8667235667f6c2bbcdbec984ca8922d9")
(setf (get common_msgs_pkg::encoder :datatype-) "common_msgs_pkg/encoder")
(setf (get common_msgs_pkg::encoder :definition-)
      "float32 right_distance
float32 left_distance
")



(provide :common_msgs_pkg/encoder "8667235667f6c2bbcdbec984ca8922d9")


