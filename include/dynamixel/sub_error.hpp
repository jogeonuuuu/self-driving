#ifndef _SUB_ERROR_HPP_
#define _SUB_ERROR_HPP_
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "dynamixel/dxl.hpp"
#include <memory>
#include <chrono>
#include <functional>
#include <thread>

using namespace std::chrono_literals;
using std::placeholders::_1;

class jetson : public rclcpp::Node 
{
private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub;
    std_msgs::msg::Int32 error;
    bool tf = false;

    Dxl dxl;

    void sub_callback(const std_msgs::msg::Int32::SharedPtr msg);

public:
    jetson();
    ~jetson();
};
#endif //_SUB_ERROR_HPP_