cmake_minimum_required(VERSION 2.8)

project(exercise_ch3)

include_directories("/usr/include/eigen3")

add_executable(assignIdentity assignIdentity.cpp)
add_executable(solveLinearEquations solveLinearEquations.cpp)

