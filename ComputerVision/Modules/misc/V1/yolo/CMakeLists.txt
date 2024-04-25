add_library(yolo yolo.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(yolo PUBLIC .)

target_include_directories(yolo PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(yolo ${OpenCV_LIBS})