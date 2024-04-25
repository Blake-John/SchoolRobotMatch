cmake_minimum_required (VERSION 3.10)
project (FILTER)


find_package (OpenCV REQUIRED)

add_executable (main main.cpp)
add_executable (kmeans kmeans.cpp)

target_include_directories (main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (main ${OpenCV_LIBS})
target_include_directories (kmeans PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (kmeans ${OpenCV_LIBS})

