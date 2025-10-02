#include "focimeccs/match_subscriber.hpp"

MatchSubscriber::MatchSubscriber(const rclcpp::NodeOptions & options)
  : rclcpp::Node("match_subscriber", options)
{
  auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
  sub_ = this->create_subscription<std_msgs::msg::UInt8>(
    "/focimeccsek", qos,
    std::bind(&MatchSubscriber::on_msg, this, std::placeholders::_1)
  );
  RCLCPP_INFO(this->get_logger(), "match_subscriber elindult");
}


void MatchSubscriber::on_msg(const std_msgs::msg::UInt8::SharedPtr msg)
{
  auto g = msg->data;
  if (g == 0) {
    RCLCPP_INFO(this->get_logger(), "Unalmas mérkőzés (0 gól)");
  } else if (g > 6) {
    RCLCPP_INFO(this->get_logger(), "Gólzápor! (%u gól)", g);
  } else {
    RCLCPP_INFO(this->get_logger(), "Eredmény: %u gól", g);
  }
}


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MatchSubscriber>());
  rclcpp::shutdown();
  return 0;
}