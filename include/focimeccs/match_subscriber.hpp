#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <string>

class MatchSubscriber : public rclcpp::Node {
public:
    explicit MatchSubscriber(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
private:
    void on_msg(const std_msgs::msg::UInt8::SharedPtr msg);
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr sub_;
};  