// generated from
// rosidl_typesupport_c/resource/rosidl_typesupport_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef RCLCPP__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_
#define RCLCPP__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_C_EXPORT_rclcpp __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_C_IMPORT_rclcpp __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_C_EXPORT_rclcpp __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_C_IMPORT_rclcpp __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_C_BUILDING_DLL_rclcpp
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_rclcpp ROSIDL_TYPESUPPORT_C_EXPORT_rclcpp
  #else
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_rclcpp ROSIDL_TYPESUPPORT_C_IMPORT_rclcpp
  #endif
#else
  #define ROSIDL_TYPESUPPORT_C_EXPORT_rclcpp __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_C_IMPORT_rclcpp
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_rclcpp __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_rclcpp
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // RCLCPP__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_
