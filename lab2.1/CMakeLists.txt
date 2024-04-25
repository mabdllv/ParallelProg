cmake_minimum_required(VERSION 3.10)
project(Lab2.1 CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(${PROJECT_NAME} main.cpp constants.h)

target_link_libraries(${PROJECT_NAME} PUBLIC MPI::MPI_CXX)