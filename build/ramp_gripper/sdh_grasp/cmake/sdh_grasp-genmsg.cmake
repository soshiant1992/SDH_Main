# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "sdh_grasp: 3 messages, 0 services")

set(MSG_I_FLAGS "-Isdh_grasp:/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(sdh_grasp_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg" NAME_WE)
add_custom_target(_sdh_grasp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sdh_grasp" "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg" ""
)

get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg" NAME_WE)
add_custom_target(_sdh_grasp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sdh_grasp" "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg" ""
)

get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg" NAME_WE)
add_custom_target(_sdh_grasp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sdh_grasp" "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp
)
_generate_msg_cpp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp
)
_generate_msg_cpp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp
)

### Generating Services

### Generating Module File
_generate_module_cpp(sdh_grasp
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(sdh_grasp_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(sdh_grasp_generate_messages sdh_grasp_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_cpp _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_cpp _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_cpp _sdh_grasp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sdh_grasp_gencpp)
add_dependencies(sdh_grasp_gencpp sdh_grasp_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sdh_grasp_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp
)
_generate_msg_lisp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp
)
_generate_msg_lisp(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp
)

### Generating Services

### Generating Module File
_generate_module_lisp(sdh_grasp
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(sdh_grasp_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(sdh_grasp_generate_messages sdh_grasp_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_lisp _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_lisp _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_lisp _sdh_grasp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sdh_grasp_genlisp)
add_dependencies(sdh_grasp_genlisp sdh_grasp_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sdh_grasp_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp
)
_generate_msg_py(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp
)
_generate_msg_py(sdh_grasp
  "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp
)

### Generating Services

### Generating Module File
_generate_module_py(sdh_grasp
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(sdh_grasp_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(sdh_grasp_generate_messages sdh_grasp_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_py _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_py _sdh_grasp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg" NAME_WE)
add_dependencies(sdh_grasp_generate_messages_py _sdh_grasp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sdh_grasp_genpy)
add_dependencies(sdh_grasp_genpy sdh_grasp_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sdh_grasp_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sdh_grasp
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(sdh_grasp_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sdh_grasp
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(sdh_grasp_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sdh_grasp
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(sdh_grasp_generate_messages_py std_msgs_generate_messages_py)
endif()
