cmake_minimum_required(VERSION 3.10)
project(V1)

add_subdirectory(yolo)
add_subdirectory(mathfunc)

add_executable(main main.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})

target_link_libraries(main yolo)
target_link_libraries(main mathfunc)