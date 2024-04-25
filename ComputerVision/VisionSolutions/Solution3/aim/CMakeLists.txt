add_library (aim STATIC aim.cpp)

find_package (OpenCV REQUIRED)

target_include_directories (aim PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries (aim ${OpenCV_LIBS})

target_include_directories (aim PUBLIC .)

target_link_libraries (aim func)
target_link_libraries (aim serial)
target_link_libraries (aim process)
target_link_libraries (aim mathfunc)

