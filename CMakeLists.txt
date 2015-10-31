cmake_minimum_required(VERSION 2.8.3)
project(nn_control_input_filter)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(poi_state_publisher src/poi_state_publisher.cpp)
target_link_libraries(poi_state_publisher ${catkin_LIBRARIES})
add_dependencies(poi_state_publisher ${catkin_EXPORTED_TARGETS})
