cmake_minimum_required(VERSION 2.8.3)
project(task)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  visualization_msgs
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

# Runner 1
add_executable(runner1 src/nodes/runner1.cpp src/helper/node.cpp src/helper/runner.cpp)
target_link_libraries(runner1 ${catkin_LIBRARIES})
add_dependencies(runner1 task_generate_messages_cpp)

# Runner 2
add_executable(runner2 src/nodes/runner2.cpp src/helper/node.cpp src/helper/runner.cpp)
target_link_libraries(runner2 ${catkin_LIBRARIES})
add_dependencies(runner2 task_generate_messages_cpp)

# Runner 3
add_executable(runner3 src/nodes/runner3.cpp src/helper/node.cpp src/helper/runner.cpp)
target_link_libraries(runner3 ${catkin_LIBRARIES})
add_dependencies(runner3 task_generate_messages_cpp)

# Runner 4
add_executable(runner4 src/nodes/runner4.cpp src/helper/node.cpp src/helper/runner.cpp)
target_link_libraries(runner4 ${catkin_LIBRARIES})
add_dependencies(runner4 task_generate_messages_cpp)

# Runner 5
add_executable(runner5 src/nodes/runner5.cpp src/helper/node.cpp src/helper/runner.cpp)
target_link_libraries(runner5 ${catkin_LIBRARIES})
add_dependencies(runner5 task_generate_messages_cpp)

# Observer
add_executable(observer src/nodes/observer.cpp src/helper/node.cpp src/helper/observer.cpp)
target_link_libraries(observer ${catkin_LIBRARIES})
add_dependencies(observer task_generate_messages_cpp)
