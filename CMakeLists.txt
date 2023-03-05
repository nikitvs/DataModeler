cmake_minimum_required(VERSION 3.0.0)
project(DataModeler VERSION 0.0.1)

# определение и настройка таргета
set(SOURCES
    src/main.cpp
    src/attribute.cpp
    src/entity.cpp
    src/model.cpp
)
set(HEADERS
    src/attribute.hpp
    src/entity.hpp
    src/model.hpp
)

add_executable(DataModeler ${SOURCES} ${HEADERS})
set_target_properties(DataModeler
    PROPERTIES
    CXX_STANDART 11
    CXX_STANDART_REQUIRED ON
)