cmake_minimum_required(VERSION 3.27)
project(main)

set(CMAKE_CXX_STANDARD 20)
#add_compile_options(-mavx2 -mfma)
add_executable(main mainCblas.cpp)
target_link_libraries(main -L/home/kest/Linux_P4SSE2/lib/)
#add_executable(main main.cpp)