cmake_minimum_required(VERSION 3.10)
project(AIM)

add_subdirectory(yolov5_dnn)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp)
# add_executable(quanti quantization.cpp)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})

# target_include_directories(quanti PUBLIC ${OpenCV_INCLUDE_DIRS})
# target_link_libraries(quanti ${OpenCV_LIBS})

target_link_libraries(main yodnn)