# Install script for directory: /home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mjmj/catkin_ws_mike/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdh_grasp/msg" TYPE FILE FILES
    "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/grasp_info.msg"
    "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/pre_grasp_pos_data.msg"
    "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg/spatial_array.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdh_grasp/cmake" TYPE FILE FILES "/home/mjmj/catkin_ws_mike/build/ramp_gripper/sdh_grasp/catkin_generated/installspace/sdh_grasp-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/mjmj/catkin_ws_mike/devel/include/sdh_grasp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/mjmj/catkin_ws_mike/devel/share/common-lisp/ros/sdh_grasp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/mjmj/catkin_ws_mike/devel/lib/python2.7/dist-packages/sdh_grasp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/mjmj/catkin_ws_mike/devel/lib/python2.7/dist-packages/sdh_grasp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/mjmj/catkin_ws_mike/build/ramp_gripper/sdh_grasp/catkin_generated/installspace/sdh_grasp.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdh_grasp/cmake" TYPE FILE FILES "/home/mjmj/catkin_ws_mike/build/ramp_gripper/sdh_grasp/catkin_generated/installspace/sdh_grasp-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdh_grasp/cmake" TYPE FILE FILES
    "/home/mjmj/catkin_ws_mike/build/ramp_gripper/sdh_grasp/catkin_generated/installspace/sdh_graspConfig.cmake"
    "/home/mjmj/catkin_ws_mike/build/ramp_gripper/sdh_grasp/catkin_generated/installspace/sdh_graspConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdh_grasp" TYPE FILE FILES "/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/package.xml")
endif()

