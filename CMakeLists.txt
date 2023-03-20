cmake_minimum_required(VERSION 3.5.0)
project(DataModeler VERSION 0.0.1)

# определить исходники
file(
    GLOB_RECURSE SOURCES
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
)
file(
    GLOB_RECURSE HEADERS
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.hpp
)

# определение и настройка таргета
add_executable(DataModeler ${SOURCES} ${HEADERS})
set_target_properties(DataModeler
    PROPERTIES
    CXX_STANDART 17
    CXX_STANDART_REQUIRED ON
)

# json
target_include_directories(DataModeler PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/json/include)
# определить файл типов данных в директорию сборки
configure_file(src/types.json ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_subdirectory(tests)