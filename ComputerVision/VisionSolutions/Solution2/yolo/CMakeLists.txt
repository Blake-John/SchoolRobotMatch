add_library (yolo STATIC yolo.cpp)

find_package (OpenCV REQUIRED)

target_include_directories (yolo PUBLIC ${OpenCV_INCLUDE_LIB})
target_link_libraries (yolo ${OpenCV_LIBS})

target_include_directories (yolo PUBLIC .)
