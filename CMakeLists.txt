 cmake_minimum_required(VERSION 3.22)

# set the project name
project(smoother VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

# GOOGLE TEST ########################
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(processor_test tests/test_processor.cpp)
target_link_libraries(processor_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(processor_test)
######################################

set(SOURCES src/smoother.cpp src/processor.cpp)

# add the executable
add_library(smoother SHARED ${SOURCES})

target_sources(smoother PRIVATE ./src)
target_include_directories(smoother PUBLIC ./include)

set_target_properties(smoother PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/processor.h
)
