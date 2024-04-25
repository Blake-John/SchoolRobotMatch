cmake_minimum_required (VERSION 3.10)
project (SOLUTION3)

add_subdirectory (func)
add_subdirectory (process)
add_subdirectory (serial)
add_subdirectory (aim)
add_subdirectory (mathfunc)

find_package (OpenCV REQUIRED)

add_executable (main main.cpp)

target_include_directories (main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (main ${OpenCV_LIBS})

target_link_libraries (main mathfunc)
target_link_libraries (main process)
target_link_libraries (main serial)
target_link_libraries (main aim)
target_link_libraries (main mathfunc)
