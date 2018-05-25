; Auto-generated. Do not edit!


(cl:in-package sdh_grasp-msg)


;//! \htmlinclude grasp_info.msg.html

(cl:defclass <grasp_info> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:boolean
    :initform cl:nil)
   (type
    :reader type
    :initarg :type
    :type cl:string
    :initform ""))
)

(cl:defclass grasp_info (<grasp_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <grasp_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'grasp_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sdh_grasp-msg:<grasp_info> is deprecated: use sdh_grasp-msg:grasp_info instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <grasp_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sdh_grasp-msg:state-val is deprecated.  Use sdh_grasp-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <grasp_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sdh_grasp-msg:type-val is deprecated.  Use sdh_grasp-msg:type instead.")
  (type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <grasp_info>) ostream)
  "Serializes a message object of type '<grasp_info>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'state) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'type))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'type))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <grasp_info>) istream)
  "Deserializes a message object of type '<grasp_info>"
    (cl:setf (cl:slot-value msg 'state) (cl:not (cl:zerop (cl:read-byte istream))))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<grasp_info>)))
  "Returns string type for a message object of type '<grasp_info>"
  "sdh_grasp/grasp_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'grasp_info)))
  "Returns string type for a message object of type 'grasp_info"
  "sdh_grasp/grasp_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<grasp_info>)))
  "Returns md5sum for a message object of type '<grasp_info>"
  "cf9efc9a129a5751020d43b2fc5efbd0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'grasp_info)))
  "Returns md5sum for a message object of type 'grasp_info"
  "cf9efc9a129a5751020d43b2fc5efbd0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<grasp_info>)))
  "Returns full string definition for message of type '<grasp_info>"
  (cl:format cl:nil "bool state~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'grasp_info)))
  "Returns full string definition for message of type 'grasp_info"
  (cl:format cl:nil "bool state~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <grasp_info>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'type))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <grasp_info>))
  "Converts a ROS message object to a list"
  (cl:list 'grasp_info
    (cl:cons ':state (state msg))
    (cl:cons ':type (type msg))
))
