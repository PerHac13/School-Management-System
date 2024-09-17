cmake_minimum_required(VERSION 3.10)
project(SchoolManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(lib)

file(GLOB SOURCES "src/*.cpp")

add_executable(SchoolManagementSystem ${SOURCES})