cmake_minimum_required(VERSION 3.10)
project(COLOR_PICKER)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp)
add_executable(maind maind.cpp)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})
target_include_directories(maind PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(maind ${OpenCV_LIBS})
