cmake_minimum_required(VERSION 3.10)
project(GETANGLE)

find_package(OpenCV REQUIRED)

add_subdirectory(mathfunc)
add_subdirectory(process)
add_subdirectory(funcs)

add_executable(main main.cpp)
target_link_libraries(main mathfunc)
target_link_libraries(main process)
target_link_libraries(main funcs)

add_executable(main2 main2.cpp)
target_link_libraries(main2 mathfunc)
target_link_libraries(main2 process)
target_link_libraries(main2 funcs)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})