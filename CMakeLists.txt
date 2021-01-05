cmake_minimum_required(VERSION 3.17)
project(ElevatorSimulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElevatorSimulation main.cpp Sources/Queue.cpp Headers/Queue.h)