cmake_minimum_required (VERSION 3.10)
project (SOLUTION2)

add_subdirectory (func)
add_subdirectory (yolo)
add_subdirectory (aim)
add_subdirectory (serial)

find_package (OpenCV REQUIRED)

add_executable (main main.cpp)

target_include_directories (main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (main ${OpenCV_LIBS})

target_link_libraries (main func)
target_link_libraries (main yolo)
target_link_libraries (main aim)
target_link_libraries (main serial)