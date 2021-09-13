cmake_minimum_required(VERSION 2.8)
project(useEigen)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")

# 添加Eigen头文件
include_directories("/usr/include/eigen3")
add_executable(eigenMatrix eigenMatrix.cpp)

# link the library 
# (for most cases, we need to do this. Here since eigen3 only includes header files, no need to do it)
# target_link_libraries(eigenMatrix PRIVATE xxx)