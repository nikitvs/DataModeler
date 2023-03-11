cmake_minimum_required(VERSION 3.0.0)
project(DataModeler VERSION 0.0.1)

# определение и настройка таргета
set(SOURCES
    src/modelComponents/relationship.cpp
    src/modelComponents/attribute.cpp
    src/modelComponents/entity.cpp
    src/main.cpp
    src/model.cpp
    src/config.cpp
)
set(HEADERS
    src/modelComponents/relationship.hpp
    src/modelComponents/attribute.hpp
    src/modelComponents/entity.hpp
    src/model.hpp
    src/config.hpp
)

add_executable(DataModeler ${SOURCES} ${HEADERS})
set_target_properties(DataModeler
    PROPERTIES
    CXX_STANDART 17
    CXX_STANDART_REQUIRED ON
)

# json
# find_package(nlohmann_json 3.2.0 REQUIRED)
target_include_directories(DataModeler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/json/include)
# target_link_libraries(DataModeler PRIVATE nlohmann_json::nlohmann_json)