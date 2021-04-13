// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rclcpp:msg/MessageWithHeader.idl
// generated code does not contain a copyright notice

#ifndef RCLCPP__MSG__DETAIL__MESSAGE_WITH_HEADER__TRAITS_HPP_
#define RCLCPP__MSG__DETAIL__MESSAGE_WITH_HEADER__TRAITS_HPP_

#include "rclcpp/msg/detail/message_with_header__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "rclcpp/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rclcpp::msg::MessageWithHeader>()
{
  return "rclcpp::msg::MessageWithHeader";
}

template<>
inline const char * name<rclcpp::msg::MessageWithHeader>()
{
  return "rclcpp/msg/MessageWithHeader";
}

template<>
struct has_fixed_size<rclcpp::msg::MessageWithHeader>
  : std::integral_constant<bool, has_fixed_size<rclcpp::msg::Header>::value> {};

template<>
struct has_bounded_size<rclcpp::msg::MessageWithHeader>
  : std::integral_constant<bool, has_bounded_size<rclcpp::msg::Header>::value> {};

template<>
struct is_message<rclcpp::msg::MessageWithHeader>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCLCPP__MSG__DETAIL__MESSAGE_WITH_HEADER__TRAITS_HPP_
