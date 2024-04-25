add_library(process process.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(process PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(process ${OpenCV_LIBS})

target_include_directories(process PUBLIC .)

target_link_libraries(process mathfunc)