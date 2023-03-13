#pragma once

#include <vector>
#include "nlohmann/json.hpp"

// используется имя json
using json = nlohmann::json;

class Config
{
private:
    std::string m_jsonDatabaseTypesPath = "./types.json";   // файл с типами атрибутов для различных СУБД
    json m_jsonTypes;                                       // содержимое json файла
public:
    Config();
    std::vector<std::string> availableDBMS();               // возвращает вектор имен доступных СУБД
    std::vector<std::string> availableDomains(std::string); // возвращает вектор имен доменов для выбранной СУБД
    std::vector<std::string> availableTypes(std::string, std::string);  /*  возвращает вектор типов данных 
                                                                            для выбранного домена выбранной СУБД */
    bool dynamicType(std::string, std::string, std::string);    // возвращает флаг динамичного размера типа данных
    ~Config();
};
