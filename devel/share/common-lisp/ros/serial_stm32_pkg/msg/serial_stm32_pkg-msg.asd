
(cl:in-package :asdf)

(defsystem "serial_stm32_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "EncoderData" :depends-on ("_package_EncoderData"))
    (:file "_package_EncoderData" :depends-on ("_package"))
  ))