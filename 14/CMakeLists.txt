cmake_minimum_required(VERSION 3.20)

project(14)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Parabolic_Reflector_Dish main.cpp)
add_executable(2_Parabolic_Reflector_Dish main2.cpp)
