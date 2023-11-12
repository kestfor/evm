cmake_minimum_required(VERSION 3.26)
project(test)

set(CMAKE_CXX_STANDARD 23)
#set(ENV{OPENCV_DIR} "C:\\opencv\\build")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

#add_executable(lab5 src/timeCheck.cpp)
add_executable(test main.cpp)
add_executable(copy test.cpp)
add_executable(maim main.c)

#add_compile_options("-l:libusb-1.0.a")
#target_link_libraries(test ${OpenCV_LIBS})