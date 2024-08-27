#include "dynamixel/sub_error.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<jetson>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}