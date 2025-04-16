;; Auto-generated. Do not edit!


(when (boundp 'yolo11_pkg::array)
  (if (not (find-package "YOLO11_PKG"))
    (make-package "YOLO11_PKG"))
  (shadow 'array (find-package "YOLO11_PKG")))
(unless (find-package "YOLO11_PKG::ARRAY")
  (make-package "YOLO11_PKG::ARRAY"))

(in-package "ROS")
;;//! \htmlinclude array.msg.html


(defclass yolo11_pkg::array
  :super ros::object
  :slots (_array ))

(defmethod yolo11_pkg::array
  (:init
   (&key
    ((:array __array) ())
    )
   (send-super :init)
   (setq _array __array)
   self)
  (:array
   (&rest __array)
   (if (keywordp (car __array))
       (send* _array __array)
     (progn
       (if __array (setq _array (car __array)))
       _array)))
  (:serialization-length
   ()
   (+
    ;; yolo11_pkg/coordinate[] _array
    (apply #'+ (send-all _array :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; yolo11_pkg/coordinate[] _array
     (write-long (length _array) s)
     (dolist (elem _array)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; yolo11_pkg/coordinate[] _array
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _array (let (r) (dotimes (i n) (push (instance yolo11_pkg::coordinate :init) r)) r))
     (dolist (elem- _array)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get yolo11_pkg::array :md5sum-) "5a32149513fa1aa3cce229c0f0ef79c6")
(setf (get yolo11_pkg::array :datatype-) "yolo11_pkg/array")
(setf (get yolo11_pkg::array :definition-)
      "coordinate[] array
================================================================================
MSG: yolo11_pkg/coordinate
int16 x
int16 y
")



(provide :yolo11_pkg/array "5a32149513fa1aa3cce229c0f0ef79c6")


