cmake_minimum_required(VERSION 2.8.4)
project(clusterizator_manager)

include(../base/common.cmake)
add_subdirectory(../base/dbscan dbscan)
add_subdirectory(../base/string_preprocessor string_preprocessor)

add_library(clusterizator_manager "clusterizator_manager.cpp")
target_link_libraries(clusterizator_manager logger dbscan string_preprocessor)

add_executable(clusterizator_manager_example "example.cpp")
target_link_libraries(clusterizator_manager_example clusterizator_manager)
set_target_properties(clusterizator_manager_example PROPERTIES OUTPUT_NAME clusterizator_manager)
