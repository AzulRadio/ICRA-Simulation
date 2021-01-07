add_executable(${PROJECT_NAME}_node get_model_state.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)