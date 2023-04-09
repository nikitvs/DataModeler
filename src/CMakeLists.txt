project(DataModeler)

set(HEADERS_PATH ${CMAKE_SOURCE_DIR}/include)

# определить исходники
file(
    GLOB_RECURSE SOURCES
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.[ch]pp
)
file(
    GLOB_RECURSE HEADERS
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${HEADERS_PATH}/*.hpp
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
target_include_directories(DataModeler PRIVATE ${HEADERS_PATH})
# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)
target_link_libraries(DataModeler PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
)
#qt5_use_modules(DataModeler Core)

# определить файл типов данных в директорию сборки
configure_file(${CMAKE_SOURCE_DIR}/types.json ${CMAKE_CURRENT_BINARY_DIR})
# определить файл бд в директорию сборки
#configure_file(${CMAKE_SOURCE_DIR}/modelDatabase.db ${CMAKE_CURRENT_BINARY_DIR})
