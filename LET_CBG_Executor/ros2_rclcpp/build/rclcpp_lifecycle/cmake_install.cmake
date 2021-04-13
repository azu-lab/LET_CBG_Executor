# Install script for directory: /home/pengbo/rclcpp_cbg/ros2_rclcpp/rclcpp_lifecycle

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pengbo/rclcpp_cbg/ros2_rclcpp/install/rclcpp_lifecycle")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/librclcpp_lifecycle.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so"
         OLD_RPATH "/home/pengbo/rclcpp_cbg/ros2_rclcpp/install/rclcpp/lib:/home/pengbo/ros2_foxy/install/rcl_lifecycle/lib:/home/pengbo/ros2_foxy/install/lifecycle_msgs/lib:/home/pengbo/ros2_foxy/install/libstatistics_collector/lib:/home/pengbo/ros2_foxy/install/std_msgs/lib:/home/pengbo/ros2_foxy/install/rosgraph_msgs/lib:/home/pengbo/ros2_foxy/install/statistics_msgs/lib:/home/pengbo/ros2_foxy/install/rcl/lib:/home/pengbo/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/pengbo/ros2_foxy/install/libyaml_vendor/lib:/home/pengbo/ros2_foxy/install/tracetools/lib:/home/pengbo/ros2_foxy/install/rcl_interfaces/lib:/home/pengbo/ros2_foxy/install/builtin_interfaces/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_c/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/pengbo/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/pengbo/ros2_foxy/install/rmw_implementation/lib:/home/pengbo/ros2_foxy/install/rcpputils/lib:/home/pengbo/ros2_foxy/install/rmw/lib:/home/pengbo/ros2_foxy/install/rcl_logging_spdlog/lib:/home/pengbo/ros2_foxy/install/rosidl_runtime_c/lib:/home/pengbo/ros2_foxy/install/rcutils/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librclcpp_lifecycle.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/ros2_foxy/install/ament_package/lib/python3.8/site-packages/ament_package/template/environment_hook/library_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/library_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/rclcpp_lifecycle")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/rclcpp_lifecycle")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/environment" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_index/share/ament_index/resource_index/packages/rclcpp_lifecycle")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport.cmake"
         "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/CMakeFiles/Export/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/CMakeFiles/Export/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/CMakeFiles/Export/share/rclcpp_lifecycle/cmake/rclcpp_lifecycleExport-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_export_include_directories/ament_cmake_export_include_directories-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_export_libraries/ament_cmake_export_libraries-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_export_targets/ament_cmake_export_targets-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_export_dependencies/ament_cmake_export_dependencies-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle/cmake" TYPE FILE FILES
    "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_core/rclcpp_lifecycleConfig.cmake"
    "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/ament_cmake_core/rclcpp_lifecycleConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rclcpp_lifecycle" TYPE FILE FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/rclcpp_lifecycle/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pengbo/rclcpp_cbg/ros2_rclcpp/rclcpp_lifecycle/include/")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/pengbo/rclcpp_cbg/ros2_rclcpp/build/rclcpp_lifecycle/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
