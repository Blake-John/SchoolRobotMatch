add_library(func func.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(func PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(func ${OpenCV_LIBS})

target_include_directories(func PUBLIC .)