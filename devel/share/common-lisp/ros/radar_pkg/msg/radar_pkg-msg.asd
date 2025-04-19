
(cl:in-package :asdf)

(defsystem "radar_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "radar" :depends-on ("_package_radar"))
    (:file "_package_radar" :depends-on ("_package"))
  ))