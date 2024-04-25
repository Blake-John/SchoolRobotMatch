add_library(yolov3 yolov3.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(yolov3 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(yolov3 ${OpenCV_LIBS})

target_include_directories(yolov3 PUBLIC .)