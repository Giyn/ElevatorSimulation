cmake_minimum_required(VERSION 3.17)
project(ElevatorSimulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElevatorSimulation main.cpp Sources/Queue.cpp Headers/Queue.h Sources/ElevatorSimulation.cpp Headers/ElevatorSimulation.h Sources/IO.cpp Sources/Passenger.cpp Sources/Stack.cpp Headers/Stack.h Headers/IO.h Headers/Passenger.h Headers/ElevatorSimulationDefinition.h)