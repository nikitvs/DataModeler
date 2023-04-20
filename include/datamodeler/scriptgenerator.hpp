#pragma once

#include "datamodeler/model/model.hpp"

// тип атрибута
class Entity;
class Attribute;

class ScriptGenerator
{
private:
	static std::string _attributeType(const Attribute* const attribute);		// возвращает тип данных с дополнительными параметрами типа
	static std::string _attributeParameters(const Attribute* const attribute);	// возвращает дополнительные параметры
	static std::string _scriptForAttribute(const std::string& attributeName,
										   const Attribute* const attribute);
	static std::string _scriptForEntity(const std::string& name,
										const Model& model);			// возвращает скрипт для сущности

public:
	static std::list<std::string> problemsReadyList(const Model& model);	// возвращает список проблем генерации
	static std::string generateScript(const Model& model);					// возвращает sql скрипт для создание БД
};
