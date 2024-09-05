#include "dynamixel/sub_error.hpp"

void jetson::sub_callback(const std_msgs::msg::Int32::SharedPtr error)
//std::function<void(MessageT)> 형의 함수만 전달가능
{
    if (Dxl::kbhit()) {
        if (dxl.getch() == 's') {
            if(tf) dxl.setVelocity(0, 0);
            tf = !tf;
        }
    }
    double gain = 1; //0.33
    if(abs(error->data) == 180) gain = 5;

    int lmotor = (100 - (gain * error->data));
    int rmotor = -(100 + (gain * error->data));
    if(tf) dxl.setVelocity(lmotor, rmotor);
    
    RCLCPP_INFO(this->get_logger(), "error: %d", error->data);
    RCLCPP_INFO(this->get_logger(), "motor: %d, %d", lmotor, rmotor);
}

jetson::jetson() : Node("errorSub_Node")
{
    if (!dxl.open()) {
        RCLCPP_ERROR(this->get_logger(), "dynamixel open error");
        rclcpp::shutdown();
    }
    sub = this->create_subscription<std_msgs::msg::Int32>("error",
        rclcpp::QoS(rclcpp::KeepLast(10)), std::bind(&jetson::sub_callback, this, _1));
}
jetson::~jetson()
{
    dxl.close();
}
