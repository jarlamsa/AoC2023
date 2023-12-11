cmake_minimum_required(VERSION 3.20)

project(11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Cosmic_Expansion main.cpp)
add_executable(2_Cosmic_Expansion main2.cpp)
