cmake_minimum_required(VERSION 3.27)
project(main)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-mavx2 -mfma)
add_executable(main1 mainCblas.cpp)
add_executable(main2 main.cpp)
add_executable(main3 mainVect.cpp)