// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rclcpp:msg/Header.idl
// generated code does not contain a copyright notice
#include "rclcpp/msg/detail/header__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
rclcpp__msg__Header__init(rclcpp__msg__Header * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    rclcpp__msg__Header__fini(msg);
    return false;
  }
  return true;
}

void
rclcpp__msg__Header__fini(rclcpp__msg__Header * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

rclcpp__msg__Header *
rclcpp__msg__Header__create()
{
  rclcpp__msg__Header * msg = (rclcpp__msg__Header *)malloc(sizeof(rclcpp__msg__Header));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rclcpp__msg__Header));
  bool success = rclcpp__msg__Header__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
rclcpp__msg__Header__destroy(rclcpp__msg__Header * msg)
{
  if (msg) {
    rclcpp__msg__Header__fini(msg);
  }
  free(msg);
}


bool
rclcpp__msg__Header__Sequence__init(rclcpp__msg__Header__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rclcpp__msg__Header * data = NULL;
  if (size) {
    data = (rclcpp__msg__Header *)calloc(size, sizeof(rclcpp__msg__Header));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rclcpp__msg__Header__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rclcpp__msg__Header__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rclcpp__msg__Header__Sequence__fini(rclcpp__msg__Header__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rclcpp__msg__Header__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rclcpp__msg__Header__Sequence *
rclcpp__msg__Header__Sequence__create(size_t size)
{
  rclcpp__msg__Header__Sequence * array = (rclcpp__msg__Header__Sequence *)malloc(sizeof(rclcpp__msg__Header__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = rclcpp__msg__Header__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
rclcpp__msg__Header__Sequence__destroy(rclcpp__msg__Header__Sequence * array)
{
  if (array) {
    rclcpp__msg__Header__Sequence__fini(array);
  }
  free(array);
}
