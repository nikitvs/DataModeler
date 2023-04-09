cmake_minimum_required(VERSION 3.5.0)
project(DataModeler VERSION 0.0.1)

# подключить json ко всем подпроектам
include_directories(DataModeler PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/json/include)

# ----- qt -----
if(WIN32)
    set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_64/lib/cmake)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# ---------------

add_subdirectory(src)
# примеры
add_subdirectory(examples)
# тесты
# enable_testing()
# add_subdirectory(tests)
