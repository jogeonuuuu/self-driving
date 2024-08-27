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

# build (auto_control)
add_executable(auto_control src/dxl.cpp src/sub_error.cpp src/s_main.cpp)
ament_target_dependencies(auto_control rclcpp std_msgs)
target_link_libraries(auto_control dxl_x64_cpp)
# build (direct_control)
add_executable(direct_control src/dxl.cpp src/d_main.cpp)
ament_target_dependencies(direct_control rclcpp std_msgs)
target_link_libraries(direct_control dxl_x64_cpp)

# Install
install(TARGETS
  auto_control
  direct_control
  DESTINATION lib/${PROJECT_NAME})

ament_package()