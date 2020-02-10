cmake_minimum_required(VERSION 3.15)
project(gtd)

set(CMAKE_CXX_STANDARD 20)

add_executable(gtd main.cpp lib/org_mode_file.h lib/org_mode_file.cpp)
