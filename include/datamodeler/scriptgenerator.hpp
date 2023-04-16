#pragma once

#include "datamodeler/model/model.hpp"

// тип атрибута
class Attribute;

class ScriptGenerator
{
private:
	static std::string _attributeType(const Attribute* const attribute);       // возвращает тип данных с дополнительными параметрами типа
	static std::string _attributeParameters(const Attribute* const attribute); // возвращает дополнительные параметры
	static std::string _scriptForEntity(const std::string& name, const Entity* const entity);	// возвращает скрипт для сущности
//	static std::vector<std::string> isReady(const Model& model);

public:
	static std::string generateScript(const Model& model);     // возвращает sql скрипт для создание БД
};
