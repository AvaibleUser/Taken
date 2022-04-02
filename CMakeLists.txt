cmake_minimum_required(VERSION 3.21)
project(Taken)

set(CMAKE_CXX_STANDARD 17)

add_executable(Taken main.cpp Node.cpp Node.h Matrix.cpp Matrix.h Reader.cpp Reader.h GameManager.cpp GameManager.h Direction.h Direction.cpp MatrixBuilder.cpp MatrixBuilder.h UtilityFunctions.cpp UtilityFunctions.h Player.cpp Player.h Ranking.cpp Ranking.h)
