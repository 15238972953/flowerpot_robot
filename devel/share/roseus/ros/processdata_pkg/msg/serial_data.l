;; Auto-generated. Do not edit!


(when (boundp 'processdata_pkg::serial_data)
  (if (not (find-package "PROCESSDATA_PKG"))
    (make-package "PROCESSDATA_PKG"))
  (shadow 'serial_data (find-package "PROCESSDATA_PKG")))
(unless (find-package "PROCESSDATA_PKG::SERIAL_DATA")
  (make-package "PROCESSDATA_PKG::SERIAL_DATA"))

(in-package "ROS")
;;//! \htmlinclude serial_data.msg.html


(defclass processdata_pkg::serial_data
  :super ros::object
  :slots (_PWM_Left _PWM_Right _command ))

(defmethod processdata_pkg::serial_data
  (:init
   (&key
    ((:PWM_Left __PWM_Left) 0)
    ((:PWM_Right __PWM_Right) 0)
    ((:command __command) 0)
    )
   (send-super :init)
   (setq _PWM_Left (round __PWM_Left))
   (setq _PWM_Right (round __PWM_Right))
   (setq _command (round __command))
   self)
  (:PWM_Left
   (&optional __PWM_Left)
   (if __PWM_Left (setq _PWM_Left __PWM_Left)) _PWM_Left)
  (:PWM_Right
   (&optional __PWM_Right)
   (if __PWM_Right (setq _PWM_Right __PWM_Right)) _PWM_Right)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:serialization-length
   ()
   (+
    ;; int8 _PWM_Left
    1
    ;; int8 _PWM_Right
    1
    ;; int8 _command
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _PWM_Left
       (write-byte _PWM_Left s)
     ;; int8 _PWM_Right
       (write-byte _PWM_Right s)
     ;; int8 _command
       (write-byte _command s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _PWM_Left
     (setq _PWM_Left (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _PWM_Left 127) (setq _PWM_Left (- _PWM_Left 256)))
   ;; int8 _PWM_Right
     (setq _PWM_Right (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _PWM_Right 127) (setq _PWM_Right (- _PWM_Right 256)))
   ;; int8 _command
     (setq _command (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _command 127) (setq _command (- _command 256)))
   ;;
   self)
  )

(setf (get processdata_pkg::serial_data :md5sum-) "55d8902ce6b1a26e186815e49dac35e0")
(setf (get processdata_pkg::serial_data :datatype-) "processdata_pkg/serial_data")
(setf (get processdata_pkg::serial_data :definition-)
      "int8 PWM_Left
int8 PWM_Right
int8 command
")



(provide :processdata_pkg/serial_data "55d8902ce6b1a26e186815e49dac35e0")


