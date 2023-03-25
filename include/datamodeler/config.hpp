#pragma once

#include <vector>
#include "nlohmann/json.hpp"

// используется имя json
using json = nlohmann::json;

class Config
{
private:
//    static const std::string m_jsonDatabaseTypesPath;   // файл с типами атрибутов для различных СУБД
    static json m_jsonTypes;                                       // содержимое json файла с типами атрибутов для различных СУБД
public:
    Config();
    static void initTypes(std::string pathToJson);
    static std::vector<std::string> availableDBMS();               // возвращает вектор имен доступных СУБД
    static std::vector<std::string> availableDomains(std::string DBMS); // возвращает вектор имен доменов для выбранной СУБД
    static std::vector<std::string> availableTypes(std::string DBMS, std::string domain);  /*  возвращает вектор типов данных
                                                                            для выбранного домена выбранной СУБД */
    static bool isDynamicType(std::string DBMS, std::string domain, std::string type);    // возвращает флаг динамичного размера типа данных
    ~Config();
};
