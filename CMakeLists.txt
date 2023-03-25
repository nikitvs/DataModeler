cmake_minimum_required(VERSION 3.5.0)
project(DataModeler VERSION 0.0.1)

# json
include_directories(DataModeler PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/json/include)

add_subdirectory(src)
add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)
