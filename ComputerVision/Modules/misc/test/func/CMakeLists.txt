add_library (func func.cpp)

target_include_directories (func PUBLIC .)
target_include_directories (func PUBLIC ${CMAKE_SOURCE_DIR}/serial)
