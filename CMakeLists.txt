cmake_minimum_required(VERSION 3.11)

project(irm_icra_simulator LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Release)
include(CheckLanguage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nodelet
  roscpp
  rospy
  sensor_msgs
  std_msgs
  cv_bridge
  shape_msgs
)

catkin_package()

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${catkin_INCLUDE_DIRS}
)

# Add subdir
add_subdirectory(examples)