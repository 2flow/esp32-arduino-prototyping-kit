cmake_minimum_required(VERSION 3.4)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIST ../src/Log.cpp
        ../test/StdLog.cpp)

add_executable(TestMain "testMain.cpp" ${SOURCE_LIST})
target_include_directories(TestMain PUBLIC "../include")
target_include_directories(TestMain PUBLIC "include")