add_library(process ./src/process.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(process PUBLIC ./inc)

target_include_directories(process PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(process ${OpenCV_LIBS})

target_link_libraries(process mathfunc)
