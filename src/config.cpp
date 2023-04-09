#include <fstream>
#include <sstream>
#include "datamodeler/config.hpp"
//#include "config.hpp"

#include <iostream>

// инициализация статических полей
json Config::m_jsonTypes;

// записывает в поле содержимое json файла
Config::Config()
{
}

// (использовать в начале!) считывает доступные СУБД и типы данных
void Config::initTypes(std::string pathToJson)
{
    std::ifstream fileInput(pathToJson);
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

// // проверить, что есть поле
// bool Config::_checkField(std::string DBMS, std::string domain, std::string type, std::string field)
// {
//     // если ключ не найден, то вернуть false
//     return !(m_jsonTypes[DBMS][domain][type].find(field).key().empty());
// }

// // проверить есть ли динамические числовые параметры
// bool Config::isSizeParameters(std::string DBMS, std::string domain, std::string type)
// {
//     return _checkField(DBMS, domain, type, "size parameters");
// }

// // проверить есть ли дополнительные текстовые параметры
// bool Config::isTextParameters(std::string DBMS, std::string domain, std::string type)
// {
//     return _checkField(DBMS, domain, type, "text parameters");
// }

// // получить нужный параметр из json
// auto Config::_getParmeter(std::string DBMS, std::string domain, std::string type, std::string field)
// {
//     // если нет таких параметров
//     if (!(_checkField(DBMS, domain, type, field))){
//         std::stringstream ss;
//         ss << "There are no such parameters in: " << DBMS << " - " << domain << " - " << type << "!";
//         throw std::invalid_argument(ss.str());
//     }
//     return m_jsonTypes[DBMS][domain][type][field];
// }

                     
// static std::string Config::domainBytype(std::string DBMS, std::string type)
// {
//     // если нет таких параметров
//     for (const auto domain : m_jsonTypes[DBMS])
//     {
        
//     }
    
//     if ([domain].find(type).key().empty()){
//         std::stringstream ss;
//         ss << "There are no such type: " << DBMS << " - " << domain << " - " << type << "!";
//         throw std::invalid_argument(ss.str());
//     }
// }

// получить нужный параметр из json
std::string  Config::typeParmetersTemplate(std::string DBMS, std::string domain, std::string type)
{
    // если нет таких параметров
    if (m_jsonTypes[DBMS][domain].find(type).key().empty()){
        std::stringstream ss;
        ss << "There are no such type: " << DBMS << " - " << domain << " - " << type << "!";
        throw std::invalid_argument(ss.str());
    }
    return m_jsonTypes[DBMS][domain][type];
}

// // получить количество параметров размера
// int Config::getSizeParametersCount(std::string DBMS, std::string domain, std::string type)
// {
//     return _getParmeter(DBMS, domain, type, "size parameters");
// }

// // получить вектор текстовых дополнительных параметров
// std::vector<std::string> Config::getTextParameters(std::string DBMS, std::string domain, std::string type)
// {
//     std::vector<std::string> res;
//     _getParmeter(DBMS, domain, type, "text parameters").get_to<std::vector<std::string>>(res);
//     return res;
// }

Config::~Config()
{
}
