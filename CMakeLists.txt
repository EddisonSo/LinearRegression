cmake_minimum_required(VERSION 3.10)
project(regression)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp matrix.cpp leastSquares.cpp houseEstimate.cpp)

