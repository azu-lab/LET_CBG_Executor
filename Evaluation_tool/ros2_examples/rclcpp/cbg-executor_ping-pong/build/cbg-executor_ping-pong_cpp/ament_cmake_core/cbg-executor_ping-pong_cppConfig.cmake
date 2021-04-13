# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cbg-executor_ping-pong_cpp_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cbg-executor_ping-pong_cpp_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cbg-executor_ping-pong_cpp_FOUND FALSE)
  elseif(NOT cbg-executor_ping-pong_cpp_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cbg-executor_ping-pong_cpp_FOUND FALSE)
  endif()
  return()
endif()
set(_cbg-executor_ping-pong_cpp_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cbg-executor_ping-pong_cpp_FIND_QUIETLY)
  message(STATUS "Found cbg-executor_ping-pong_cpp: 0.0.1 (${cbg-executor_ping-pong_cpp_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cbg-executor_ping-pong_cpp' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${cbg-executor_ping-pong_cpp_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cbg-executor_ping-pong_cpp_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${cbg-executor_ping-pong_cpp_DIR}/${_extra}")
endforeach()
