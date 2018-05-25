
(cl:in-package :asdf)

(defsystem "sdh_grasp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "pre_grasp_pos_data" :depends-on ("_package_pre_grasp_pos_data"))
    (:file "_package_pre_grasp_pos_data" :depends-on ("_package"))
    (:file "grasp_info" :depends-on ("_package_grasp_info"))
    (:file "_package_grasp_info" :depends-on ("_package"))
    (:file "spatial_array" :depends-on ("_package_spatial_array"))
    (:file "_package_spatial_array" :depends-on ("_package"))
  ))