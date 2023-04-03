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
protected:
    static bool _checkField(std::string DBMS, std::string domain, std::string type, std::string field);    // проверить, что есть поле
    static auto _getParmeter(std::string DBMS, std::string domain, std::string type, std::string field);
public:
    Config();
    static void initTypes(std::string pathToJson);                          // (использовать в начале!) считывает доступные СУБД и типы данных
    static std::vector<std::string> availableDBMS();                        // возвращает вектор имен доступных СУБД
    static std::vector<std::string> availableDomains(std::string DBMS);     // возвращает вектор имен доменов для выбранной СУБД
    static std::vector<std::string> availableTypes(std::string DBMS, std::string domain); /*  возвращает вектор типов данных
                                                                                              для выбранного домена выбранной СУБД */
                                                                                              
    // static std::string domainBytype(std::string DBMS, std::string type);
    static std::string typeParmetersTemplate(std::string DBMS, std::string domain, std::string type);
    // static bool isSizeParameters(std::string DBMS, std::string domain, std::string type);   // проверить есть ли динамические числовые параметры
    // static bool isTextParameters(std::string DBMS, std::string domain, std::string type);   // проверить есть ли дополнительные текстовые параметры
    // static int getSizeParametersCount(std::string DBMS, std::string domain, std::string type);
    // static std::vector<std::string> getTextParameters(std::string DBMS, std::string domain, std::string type);
    ~Config();
};
