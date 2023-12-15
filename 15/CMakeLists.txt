cmake_minimum_required(VERSION 3.20)

project(15)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Lens_Library main.cpp)
add_executable(2_Lens_Library main2.cpp)
