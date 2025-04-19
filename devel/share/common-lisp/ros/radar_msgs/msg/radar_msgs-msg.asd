
(cl:in-package :asdf)

(defsystem "radar_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "array" :depends-on ("_package_array"))
    (:file "_package_array" :depends-on ("_package"))
    (:file "radar" :depends-on ("_package_radar"))
    (:file "_package_radar" :depends-on ("_package"))
  ))