# Install script for directory: /home/pengbo/rclcpp_cbg/ros2_rclcpp/rclcpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pengbo/rclcpp_cbg/install/rclcpp")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/pengbo/rclcpp_cbg/build/rclcpp/ament_cmake_symlink_install/ament_cmake_symlink_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pengbo/rclcpp_cbg/build/rclcpp/librclcpp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so"
         OLD_RPATH "/home/pengbo/ros2_foxy/install/libstatistics_collector/lib:/home/pengbo/ros2_foxy/install/rcl/lib:/home/pengbo/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/pengbo/ros2_foxy/install/rosgraph_msgs/lib:/home/pengbo/ros2_foxy/install/statistics_msgs/lib:/home/pengbo/ros2_foxy/install/tracetools/lib:/home/pengbo/ros2_foxy/install/libyaml_vendor/lib:/home/pengbo/ros2_foxy/install/rcl_interfaces/lib:/home/pengbo/ros2_foxy/install/rmw_implementation/lib:/home/pengbo/ros2_foxy/install/rmw/lib:/home/pengbo/ros2_foxy/install/rcl_logging_spdlog/lib:/home/pengbo/ros2_foxy/install/std_msgs/lib:/home/pengbo/ros2_foxy/install/builtin_interfaces/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_c/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/pengbo/ros2_foxy/install/rcpputils/lib:/home/pengbo/ros2_foxy/install/rosidl_runtime_c/lib:/home/pengbo/ros2_foxy/install/rcutils/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake/rclcppExport.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake/rclcppExport.cmake"
         "/home/pengbo/rclcpp_cbg/build/rclcpp/CMakeFiles/Export/share/rclcpp/cmake/rclcppExport.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake/rclcppExport-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake/rclcppExport.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/build/rclcpp/CMakeFiles/Export/share/rclcpp/cmake/rclcppExport.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/build/rclcpp/CMakeFiles/Export/share/rclcpp/cmake/rclcppExport-noconfig.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pengbo/rclcpp_cbg/build/rclcpp/rclcpp_test_msgs__py/cmake_install.cmake")
  include("/home/pengbo/rclcpp_cbg/build/rclcpp/gtest/cmake_install.cmake")
  include("/home/pengbo/rclcpp_cbg/build/rclcpp/gmock/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/pengbo/rclcpp_cbg/build/rclcpp/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
