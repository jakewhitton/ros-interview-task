cmake_minimum_required(VERSION 2.8.3)
project(task)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  position.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#   CATKIN_DEPENDS message_runtime roscpp rospy std_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(runner src/runner_node.cpp src/node.cpp src/runner.cpp)
target_link_libraries(runner ${catkin_LIBRARIES})
add_dependencies(runner task_generate_messages_cpp)
