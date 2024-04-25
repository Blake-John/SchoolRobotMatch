add_library(mathfunc mathfunc.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(mathfunc PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(mathfunc ${OpenCV_LIBS})

target_include_directories(mathfunc PUBLIC .)