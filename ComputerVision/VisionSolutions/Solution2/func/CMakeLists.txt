add_library (func STATIC func.cpp)

find_package (OpenCV REQUIRED)

target_include_directories (func PUBLIC ${OpenCV_INCLUDE_LIB})
target_link_libraries (func ${OpenCV_LIBS})

target_include_directories (func PUBLIC .)
target_link_libraries (func yolo)
