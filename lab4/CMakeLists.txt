cmake_minimum_required(VERSION 3.10)
project(Lab4 CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OPENMP REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
