#pragma once

#include <vector>
#include "nlohmann/json.hpp"

// используется имя json
using json = nlohmann::json;

class Config
{
private:
	static json m_jsonTypes;	// содержимое json файла с типами атрибутов для различных СУБД
public:
    static void initTypes(std::string pathToJson);                          // (использовать в начале!) считывает доступные СУБД и типы данных
	static std::vector<std::string> availableDBMS();                        // получить вектор имен доступных СУБД
	static std::vector<std::string> availableDomains(std::string DBMS);     // получить вектор имен доменов для выбранной СУБД
	static std::vector<std::string> availableTypes(std::string DBMS,
												   std::string domain); /*  получить вектор типов данных
																			для выбранного домена выбранной СУБД */
	static std::string typeParmetersTemplate(std::string DBMS,
											 std::string domain,
											 std::string type);				// получить шаблон параметров
};
