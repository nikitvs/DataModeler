project(DataModeler)

# определить исходники
file(
    GLOB_RECURSE SOURCES
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
)

# определение и настройка таргета
add_library(DataModeler ${SOURCES} ${HEADERS})
set_target_properties(DataModeler
    PROPERTIES
    CXX_STANDART 17
    CXX_STANDART_REQUIRED ON
)
# Добавляем синоним для библиотеки
add_library(DataModeler::DataModeler ALIAS DataModeler)
target_include_directories(DataModeler PRIVATE ../include)

# определить файл типов данных в директорию сборки
configure_file(${CMAKE_SOURCE_DIR}/types.json ${CMAKE_CURRENT_BINARY_DIR})
