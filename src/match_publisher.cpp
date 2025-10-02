#include "focimeccs/match_publisher.hpp"

MatchPublisher::MatchPublisher(const rclcpp::NodeOptions & options)
  : rclcpp::Node("match_publisher", options)
{
  //QoS depth=10
  auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
  pub_ = this->create_publisher<std_msgs::msg::UInt8>("/focimeccsek", qos);
  this->declare_parameter<double>("goal_rate", goal_rate_);
  this->get_parameter("goal_rate", goal_rate_);

  setup_parameter_callback();
  using namespace std::chrono_literals;
  timer_ = this->create_wall_timer(1s, std::bind(&MatchPublisher::on_timer, this));
  RCLCPP_INFO(this->get_logger(), "match_publisher elindult (goal_rate=%.2f)", goal_rate_);
}

void MatchPublisher::setup_parameter_callback()
{
  param_cb_ = this->add_on_set_parameters_callback(
    [this](const std::vector<rclcpp::Parameter> & params) {
      rcl_interfaces::msg::SetParametersResult result;
      result.successful = true;
      for (const auto & p : params) {
        if (p.get_name() == "goal_rate") {
          double v = p.as_double();
          if (v <= 0.0) {
            result.successful = false;
            result.reason = "goal_rate must be > 0";
          } else {
            goal_rate_ = v;
            RCLCPP_INFO(this->get_logger(), "goal_rate új érték: %.2f", goal_rate_);
          }
        }
      }
      return result;
    }
  );
}


void MatchPublisher::on_timer()
{
  std::poisson_distribution<int> pois(goal_rate_);
  int goals = std::max(0, pois(rng_));
  goals = std::min(goals, 255);

  std_msgs::msg::UInt8 msg;
  msg.data = static_cast<uint8_t>(goals);
  pub_->publish(msg);

  RCLCPP_INFO(this->get_logger(), "Publikálva gólszám: %d", goals);
}


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MatchPublisher>());
  rclcpp::shutdown();
  return 0;
}