cmake_minimum_required(VERSION 3.5.0)
project(DataModeler VERSION 0.0.1)

# подключить json ко всем подпроектам
include_directories(DataModeler PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/json/include)
# хедеры
# install(DIRECTORY include/datamodeler DESTINATION include)
# исходники
add_subdirectory(src)
# примеры
add_subdirectory(examples)
# тесты
# enable_testing()
# add_subdirectory(tests)
