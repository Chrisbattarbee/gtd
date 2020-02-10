cmake_minimum_required(VERSION 3.13)
project(gtd)

set(CMAKE_CXX_STANDARD 20)

add_executable(gtd main.cpp lib/org_mode_file.h lib/org_mode_file.cpp lib/CLI11.hpp lib/gtd.cpp lib/gtd.h lib/subcommands/add_subcommand.cpp lib/subcommands/add_subcommand.h lib/subcommands/search_subcommand.cpp lib/subcommands/search_subcommand.h lib/subcommands/utils.cpp lib/subcommands/utils.h lib/subcommands/list_subcommand.cpp lib/subcommands/list_subcommand.h lib/subcommands/view_subcommand.cpp lib/subcommands/view_subcommand.h)
