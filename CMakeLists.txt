 cmake_minimum_required(VERSION 3.22)

# set the project name
project(Processor)

set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(Processor main.cpp processor.cpp)
