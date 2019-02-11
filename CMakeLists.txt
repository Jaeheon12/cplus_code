cmake_minimum_required(VERSION 3.13)
project(cplus_asg1)

set(CMAKE_CXX_STANDARD 14)

add_executable(cplus_asg1 main.cpp page_rank.hpp page_rank.cpp connectivity_matrix.hpp connectivity_matrix.cpp)