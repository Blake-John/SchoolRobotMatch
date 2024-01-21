add_library(funcs ./src/funcs.cpp)

target_include_directories(funcs PUBLIC ./inc)
target_link_libraries(funcs process)
target_link_libraries(funcs mathfunc)