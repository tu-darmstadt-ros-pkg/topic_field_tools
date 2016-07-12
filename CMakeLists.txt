cmake_minimum_required(VERSION 2.8.3)
project(topic_field_tools)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  topic_tools
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES topic_field_tools
#  CATKIN_DEPENDS roscpp topic_tools
#  DEPENDS system_lib
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(navsat_frame_id_changer src/navsat_frame_id_changer.cpp)
target_link_libraries(navsat_frame_id_changer ${catkin_LIBRARIES})

add_executable(imu_frame_id_changer src/imu_frame_id_changer.cpp)
target_link_libraries(imu_frame_id_changer ${catkin_LIBRARIES})
