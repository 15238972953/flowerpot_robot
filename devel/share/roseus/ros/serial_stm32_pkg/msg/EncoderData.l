;; Auto-generated. Do not edit!


(when (boundp 'serial_stm32_pkg::EncoderData)
  (if (not (find-package "SERIAL_STM32_PKG"))
    (make-package "SERIAL_STM32_PKG"))
  (shadow 'EncoderData (find-package "SERIAL_STM32_PKG")))
(unless (find-package "SERIAL_STM32_PKG::ENCODERDATA")
  (make-package "SERIAL_STM32_PKG::ENCODERDATA"))

(in-package "ROS")
;;//! \htmlinclude EncoderData.msg.html


(defclass serial_stm32_pkg::EncoderData
  :super ros::object
  :slots (_Encoder_Left _Encoder_Right ))

(defmethod serial_stm32_pkg::EncoderData
  (:init
   (&key
    ((:Encoder_Left __Encoder_Left) 0)
    ((:Encoder_Right __Encoder_Right) 0)
    )
   (send-super :init)
   (setq _Encoder_Left (round __Encoder_Left))
   (setq _Encoder_Right (round __Encoder_Right))
   self)
  (:Encoder_Left
   (&optional __Encoder_Left)
   (if __Encoder_Left (setq _Encoder_Left __Encoder_Left)) _Encoder_Left)
  (:Encoder_Right
   (&optional __Encoder_Right)
   (if __Encoder_Right (setq _Encoder_Right __Encoder_Right)) _Encoder_Right)
  (:serialization-length
   ()
   (+
    ;; uint32 _Encoder_Left
    4
    ;; uint32 _Encoder_Right
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _Encoder_Left
       (write-long _Encoder_Left s)
     ;; uint32 _Encoder_Right
       (write-long _Encoder_Right s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _Encoder_Left
     (setq _Encoder_Left (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _Encoder_Right
     (setq _Encoder_Right (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get serial_stm32_pkg::EncoderData :md5sum-) "4f445708b5fc7868c7f94d572914b055")
(setf (get serial_stm32_pkg::EncoderData :datatype-) "serial_stm32_pkg/EncoderData")
(setf (get serial_stm32_pkg::EncoderData :definition-)
      "uint32 Encoder_Left
uint32 Encoder_Right
")



(provide :serial_stm32_pkg/EncoderData "4f445708b5fc7868c7f94d572914b055")


