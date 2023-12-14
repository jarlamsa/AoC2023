cmake_minimum_required(VERSION 3.20)

project(13)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Point_of_Incidence main.cpp)
add_executable(2_Point_of_Incidence main2.cpp)
