// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rclcpp:msg/Header.idl
// generated code does not contain a copyright notice

#ifndef RCLCPP__MSG__DETAIL__HEADER__TRAITS_HPP_
#define RCLCPP__MSG__DETAIL__HEADER__TRAITS_HPP_

#include "rclcpp/msg/detail/header__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rclcpp::msg::Header>()
{
  return "rclcpp::msg::Header";
}

template<>
inline const char * name<rclcpp::msg::Header>()
{
  return "rclcpp/msg/Header";
}

template<>
struct has_fixed_size<rclcpp::msg::Header>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<rclcpp::msg::Header>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<rclcpp::msg::Header>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCLCPP__MSG__DETAIL__HEADER__TRAITS_HPP_
