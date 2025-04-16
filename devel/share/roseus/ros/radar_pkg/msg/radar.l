;; Auto-generated. Do not edit!


(when (boundp 'radar_pkg::radar)
  (if (not (find-package "RADAR_PKG"))
    (make-package "RADAR_PKG"))
  (shadow 'radar (find-package "RADAR_PKG")))
(unless (find-package "RADAR_PKG::RADAR")
  (make-package "RADAR_PKG::RADAR"))

(in-package "ROS")
;;//! \htmlinclude radar.msg.html


(defclass radar_pkg::radar
  :super ros::object
  :slots (_n _r _phi ))

(defmethod radar_pkg::radar
  (:init
   (&key
    ((:n __n) 0)
    ((:r __r) 0.0)
    ((:phi __phi) 0.0)
    )
   (send-super :init)
   (setq _n (round __n))
   (setq _r (float __r))
   (setq _phi (float __phi))
   self)
  (:n
   (&optional __n)
   (if __n (setq _n __n)) _n)
  (:r
   (&optional __r)
   (if __r (setq _r __r)) _r)
  (:phi
   (&optional __phi)
   (if __phi (setq _phi __phi)) _phi)
  (:serialization-length
   ()
   (+
    ;; int8 _n
    1
    ;; float32 _r
    4
    ;; float32 _phi
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _n
       (write-byte _n s)
     ;; float32 _r
       (sys::poke _r (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _phi
       (sys::poke _phi (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _n
     (setq _n (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _n 127) (setq _n (- _n 256)))
   ;; float32 _r
     (setq _r (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _phi
     (setq _phi (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get radar_pkg::radar :md5sum-) "b3a8cc87ce2d38b8fa7a080b864bbe8e")
(setf (get radar_pkg::radar :datatype-) "radar_pkg/radar")
(setf (get radar_pkg::radar :definition-)
      "int8 n
float32 r
float32 phi
")



(provide :radar_pkg/radar "b3a8cc87ce2d38b8fa7a080b864bbe8e")


