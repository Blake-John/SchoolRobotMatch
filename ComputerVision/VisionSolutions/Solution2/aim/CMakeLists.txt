add_library (aim STATIC aim.cpp)

find_package (OpenCV REQUIRED)

target_include_directories (aim PUBLIC ${OpenCV_INCLUDE_LIB})
target_link_libraries (aim ${OpenCV_LIBS})

target_include_directories (aim PUBLIC .)
target_link_libraries (aim yolo)
target_link_libraries (aim func)
target_link_libraries (aim serial)
