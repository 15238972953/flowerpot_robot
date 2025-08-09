
(cl:in-package :asdf)

(defsystem "tracking_pkg1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "track" :depends-on ("_package_track"))
    (:file "_package_track" :depends-on ("_package"))
  ))