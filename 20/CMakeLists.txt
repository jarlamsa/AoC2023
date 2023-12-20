cmake_minimum_required(VERSION 3.20)

project(20)
set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Pulse_Propagation main.cpp)
add_executable(2_Pulse_Propagation main2.cpp)
