;; Auto-generated. Do not edit!


(when (boundp 'common_msgs_pkg::serial_data)
  (if (not (find-package "COMMON_MSGS_PKG"))
    (make-package "COMMON_MSGS_PKG"))
  (shadow 'serial_data (find-package "COMMON_MSGS_PKG")))
(unless (find-package "COMMON_MSGS_PKG::SERIAL_DATA")
  (make-package "COMMON_MSGS_PKG::SERIAL_DATA"))

(in-package "ROS")
;;//! \htmlinclude serial_data.msg.html


(defclass common_msgs_pkg::serial_data
  :super ros::object
  :slots (_PWM_Left _PWM_Right _command _clear_encoder ))

(defmethod common_msgs_pkg::serial_data
  (:init
   (&key
    ((:PWM_Left __PWM_Left) 0)
    ((:PWM_Right __PWM_Right) 0)
    ((:command __command) 0)
    ((:clear_encoder __clear_encoder) nil)
    )
   (send-super :init)
   (setq _PWM_Left (round __PWM_Left))
   (setq _PWM_Right (round __PWM_Right))
   (setq _command (round __command))
   (setq _clear_encoder __clear_encoder)
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
  (:clear_encoder
   (&optional (__clear_encoder :null))
   (if (not (eq __clear_encoder :null)) (setq _clear_encoder __clear_encoder)) _clear_encoder)
  (:serialization-length
   ()
   (+
    ;; int8 _PWM_Left
    1
    ;; int8 _PWM_Right
    1
    ;; int8 _command
    1
    ;; bool _clear_encoder
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
     ;; bool _clear_encoder
       (if _clear_encoder (write-byte -1 s) (write-byte 0 s))
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
   ;; bool _clear_encoder
     (setq _clear_encoder (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get common_msgs_pkg::serial_data :md5sum-) "23aa005a44d993632cdb1134fc156a3a")
(setf (get common_msgs_pkg::serial_data :datatype-) "common_msgs_pkg/serial_data")
(setf (get common_msgs_pkg::serial_data :definition-)
      "int8 PWM_Left
int8 PWM_Right
int8 command
bool clear_encoder
")



(provide :common_msgs_pkg/serial_data "23aa005a44d993632cdb1134fc156a3a")


