cmake_minimum_required(VERSION 3.21)
project(Taken)

set(CMAKE_CXX_STANDARD 17)

add_executable(Taken src/main.cpp src/structures/OrthogonalMatrix.hpp src/structures/Node.hpp)
