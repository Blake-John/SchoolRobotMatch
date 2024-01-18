add_executable(shoot shoot.cpp)
add_executable(pick pick.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(shoot PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(shoot ${OpenCV_LIBS})

target_include_directories(pick PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(pick ${OpenCV_LIBS})
