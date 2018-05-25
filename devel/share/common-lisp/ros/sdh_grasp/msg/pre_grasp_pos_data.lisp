; Auto-generated. Do not edit!


(cl:in-package sdh_grasp-msg)


;//! \htmlinclude pre_grasp_pos_data.msg.html

(cl:defclass <pre_grasp_pos_data> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (type
    :reader type
    :initarg :type
    :type cl:string
    :initform ""))
)

(cl:defclass pre_grasp_pos_data (<pre_grasp_pos_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pre_grasp_pos_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pre_grasp_pos_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sdh_grasp-msg:<pre_grasp_pos_data> is deprecated: use sdh_grasp-msg:pre_grasp_pos_data instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <pre_grasp_pos_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sdh_grasp-msg:data-val is deprecated.  Use sdh_grasp-msg:data instead.")
  (data m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <pre_grasp_pos_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sdh_grasp-msg:type-val is deprecated.  Use sdh_grasp-msg:type instead.")
  (type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pre_grasp_pos_data>) ostream)
  "Serializes a message object of type '<pre_grasp_pos_data>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'data))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'type))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'type))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pre_grasp_pos_data>) istream)
  "Deserializes a message object of type '<pre_grasp_pos_data>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'type) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pre_grasp_pos_data>)))
  "Returns string type for a message object of type '<pre_grasp_pos_data>"
  "sdh_grasp/pre_grasp_pos_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pre_grasp_pos_data)))
  "Returns string type for a message object of type 'pre_grasp_pos_data"
  "sdh_grasp/pre_grasp_pos_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pre_grasp_pos_data>)))
  "Returns md5sum for a message object of type '<pre_grasp_pos_data>"
  "4d52d6e0d781ec5908fc845dc781b11d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pre_grasp_pos_data)))
  "Returns md5sum for a message object of type 'pre_grasp_pos_data"
  "4d52d6e0d781ec5908fc845dc781b11d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pre_grasp_pos_data>)))
  "Returns full string definition for message of type '<pre_grasp_pos_data>"
  (cl:format cl:nil "float64[] data~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pre_grasp_pos_data)))
  "Returns full string definition for message of type 'pre_grasp_pos_data"
  (cl:format cl:nil "float64[] data~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pre_grasp_pos_data>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:length (cl:slot-value msg 'type))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pre_grasp_pos_data>))
  "Converts a ROS message object to a list"
  (cl:list 'pre_grasp_pos_data
    (cl:cons ':data (data msg))
    (cl:cons ':type (type msg))
))
