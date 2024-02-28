add_library(readcolor readcolor.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(readcolor PUBLIC .)

target_include_directories(readcolor PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(readcolor ${OpenCV_LIBRARIES})
