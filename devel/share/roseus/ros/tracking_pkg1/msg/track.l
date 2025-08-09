;; Auto-generated. Do not edit!


(when (boundp 'tracking_pkg1::track)
  (if (not (find-package "TRACKING_PKG1"))
    (make-package "TRACKING_PKG1"))
  (shadow 'track (find-package "TRACKING_PKG1")))
(unless (find-package "TRACKING_PKG1::TRACK")
  (make-package "TRACKING_PKG1::TRACK"))

(in-package "ROS")
;;//! \htmlinclude track.msg.html


(defclass tracking_pkg1::track
  :super ros::object
  :slots (_line ))

(defmethod tracking_pkg1::track
  (:init
   (&key
    ((:line __line) (make-array 4 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _line __line)
   self)
  (:line
   (&optional __line)
   (if __line (setq _line __line)) _line)
  (:serialization-length
   ()
   (+
    ;; int16[4] _line
    (* 2    4)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16[4] _line
     (dotimes (i 4)
       (write-word (elt _line i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16[4] _line
   (dotimes (i (length _line))
     (setf (elt _line i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;;
   self)
  )

(setf (get tracking_pkg1::track :md5sum-) "6d30351f4c1b67d57e1e20725088b7c6")
(setf (get tracking_pkg1::track :datatype-) "tracking_pkg1/track")
(setf (get tracking_pkg1::track :definition-)
      "int16[4] line
")



(provide :tracking_pkg1/track "6d30351f4c1b67d57e1e20725088b7c6")


