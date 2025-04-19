
(cl:in-package :asdf)

(defsystem "yolo11_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "array" :depends-on ("_package_array"))
    (:file "_package_array" :depends-on ("_package"))
    (:file "coordinate" :depends-on ("_package_coordinate"))
    (:file "_package_coordinate" :depends-on ("_package"))
  ))