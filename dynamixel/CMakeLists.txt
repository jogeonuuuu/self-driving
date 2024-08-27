cmake_minimum_required(VERSION 3.16)
project(dynamixel)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)
include_directories(/usr/local/include/dynamixel_sdk)

# build
add_executable(control src/dxl.cpp src/error_sub.cpp src/main.cpp)
ament_target_dependencies(control rclcpp std_msgs)
target_link_libraries(control dxl_x64_cpp)

# Install
install(TARGETS
  control
  DESTINATION lib/${PROJECT_NAME})

ament_package()