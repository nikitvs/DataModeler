#include "config.hpp"
#include <fstream>
#include <iostream>

// записывает в поле содержимое json файла
Config::Config()
{
    std::ifstream fileInput(m_jsonDatabaseTypesPath);
    m_jsonTypes = json::parse(fileInput);
}

// возвращает вектор имен доступных СУБД
std::vector<std::string> Config::availableDBMS()
{
    std::vector<std::string> listDBMS;
    for(auto iter = m_jsonTypes.begin(); iter!=m_jsonTypes.end(); ++iter)
    {
        listDBMS.push_back(iter.key());
    }
    return listDBMS;
}

// возвращает вектор имен доменов для выбранной СУБД
std::vector<std::string> Config::availableDomains(std::string DBMS)
{
    std::vector<std::string> listDomains;
    for(auto iter = m_jsonTypes[DBMS].begin(); iter!=m_jsonTypes[DBMS].end(); ++iter)
    {
        listDomains.push_back(iter.key());
    }
    return listDomains;
}

// возвращает вектор типов данных для выбранного домена выбранной СУБД
std::vector<std::string> Config::availableTypes(std::string DBMS, std::string domain)
{
    std::vector<std::string> listTypes;
    for(auto iter = m_jsonTypes[DBMS][domain].begin(); iter!=m_jsonTypes[DBMS][domain].end(); ++iter)
    {
        listTypes.push_back(iter.key());
    }
    return listTypes;
}

// возвращает флаг динамичного размера типа данных
bool Config::dynamicType(std::string DBMS, std::string domain, std::string type)
{
    return m_jsonTypes[DBMS][domain][type];
}

Config::~Config()
{
}