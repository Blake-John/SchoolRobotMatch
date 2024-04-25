cmake_minimum_required(VERSION 3.10)
project(SHOOT)

add_executable(shoot shoot.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(shoot PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(shoot ${OpenCV_LIBS})