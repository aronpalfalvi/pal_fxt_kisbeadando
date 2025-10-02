cmake_minimum_required(VERSION 3.5)
project(pal_fxt_kisbeadando)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

# Publisher node
add_executable(match_publisher src/match_publisher.cpp)
ament_target_dependencies(match_publisher rclcpp std_msgs)

# Subscriber node
add_executable(match_subscriber src/match_subscriber.cpp)
ament_target_dependencies(match_subscriber rclcpp std_msgs)

install(TARGETS
  match_publisher
  match_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
