cmake_minimum_required(VERSION 3.15)
project(gtd)

set(CMAKE_CXX_STANDARD 20)

add_executable(gtd main.cpp lib/org_mode_file.h lib/org_mode_file.cpp lib/CLI11.hpp lib/gtd.cpp lib/gtd.h lib/subcommands/add_subcommand.cpp lib/subcommands/add_subcommand.h lib/subcommands/search_subcommand.cpp lib/subcommands/search_subcommand.h)
