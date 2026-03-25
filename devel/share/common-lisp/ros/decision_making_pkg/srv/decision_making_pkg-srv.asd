
(cl:in-package :asdf)

(defsystem "decision_making_pkg-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "StartTransport" :depends-on ("_package_StartTransport"))
    (:file "_package_StartTransport" :depends-on ("_package"))
  ))