project(soundex)
cmake_minimum_required(VERSION 2.8)
include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild)
add_definitions(-std=c++0x -v)


set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")



aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} gtest)

