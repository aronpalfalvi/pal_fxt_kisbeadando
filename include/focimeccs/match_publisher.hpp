#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <random>
#include <chrono>

class MatchPublisher : public rclcpp::Node {
public:
    explicit MatchPublisher(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
private:
    void on_timer();
    void setup_parameter_callback();
    rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    double goal_rate_ {2.5};//Poisson - lambda
    std::mt19937 rng_ {static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())};
    rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_cb_;
};