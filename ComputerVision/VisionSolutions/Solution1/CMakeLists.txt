cmake_minimum_required(VERSION 3.10)
project(MIDTERM)

add_subdirectory(yolo)
add_subdirectory(mathfunc)
add_subdirectory(serial)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})

target_link_libraries(main mathfunc)
# target_link_libraries(main yolo)
target_link_libraries(main serial)
