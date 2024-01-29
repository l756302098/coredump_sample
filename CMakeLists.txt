cmake_minimum_required(VERSION 3.5)

# Set the project name
project (core_samples)

set(CMAKE_CXX_FLAGS "-O2 -Wall -g -std=c++11")
set(CMAKE_BUILD_TYPE Release)

message("current dir:",${PROJECT_SOURCE_DIR})

add_executable(core_samples src/main.cpp)

target_link_libraries(core_samples pthread glog)