cmake_minimum_required(VERSION 3.20)

project(7)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Camel_Cards main.cpp)
add_executable(2_Camel_Cards main2.cpp)
