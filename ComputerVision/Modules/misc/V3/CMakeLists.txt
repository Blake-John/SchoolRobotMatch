cmake_minimum_required(VERSION 3.10)
project(V3)

add_subdirectory(ReadColorRange)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBRARIES})

target_link_libraries(main readcolor)
