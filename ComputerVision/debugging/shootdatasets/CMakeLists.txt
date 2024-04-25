cmake_minimum_required (VERSION 3.10)
project (SHOOT)

find_package (OpenCV REQUIRED)

add_executable (main main.cpp)
add_executable (test test.cpp)

target_include_directories (main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (main ${OpenCV_LIBS})

target_include_directories (test PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (test ${OpenCV_LIBS})
