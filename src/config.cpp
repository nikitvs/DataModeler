#include <fstream>
#include <sstream>
#include "datamodeler/config.hpp"
#include <QString>

// инициализация статических полей
json Config::m_jsonTypes;

// (использовать в начале!) считывает доступные СУБД и типы данных
void Config::initTypes(std::string pathToJson)
{
	std::ifstream fileInput(pathToJson);
	std::stringstream replacedInput;
	std::string line;
	while (std::getline(fileInput, line)) {
		replacedInput << QString::fromStdString(line).replace('\\', "\\\\").toStdString();
	}
	m_jsonTypes = json::parse(replacedInput);
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
