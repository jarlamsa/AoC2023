cmake_minimum_required(VERSION 3.20)

project(10)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Pipe_Maze main.cpp)
add_executable(2_Pipe_Maze main2.cpp)
