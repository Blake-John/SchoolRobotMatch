add_library(yodnn yolov5_dnn.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(yodnn PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(yodnn ${OpenCV_LIBS})

target_include_directories(yodnn PUBLIC ./)