cmake_minimum_required(VERSION 3.0.0)
project(quickcsv VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(quickcsv tests/case1.cpp)

