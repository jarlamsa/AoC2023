cmake_minimum_required(VERSION 3.20)

project(18)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Lavaduct_Lagoon main.cpp)
add_executable(2_The_Floor_Will_Be_Lava main2.cpp)
