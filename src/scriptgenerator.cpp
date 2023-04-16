#include "datamodeler/scriptgenerator.hpp"
#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/relationship.hpp"

#include <sstream>

// возвращает тип данных с дополнительными параметрами
std::string ScriptGenerator::_attributeType(const Attribute* const attribute)
{
	return attribute->type() + attribute->parameters();
}

// возвращает дополнительные параметры
std::string ScriptGenerator::_attributeParameters(const Attribute* const attribute)
{
    std::string parameters;
    if (attribute->primaryKey()){
        parameters += "PRIMARY KEY";
    } else {
        if (attribute->nullable()){
            parameters += "NULL";
        } else {
            parameters += "NOT NULL";
        };
    }
    return parameters;
}

std::string ScriptGenerator::_scriptForEntity(const std::string& name, const Entity* const entity)
{
	std::string endCommand		   = ";\n";
	std::string endStr			   = ",\n";
	std::string tab				   = "    ";
	std::string openingParenthesis = "\n(\n";
    std::string closingParenthesis = ")";

    std::stringstream script;
	script << "CREATE TABLE " << name;
    // если атрибуты есть
    if (entity->attributes().size() > 0)
    {
        script << openingParenthesis;
        for (const auto & curAttributeName : entity->attributes()) {
            const Attribute* curAttribute = entity->attribute(curAttributeName);
			script << tab << curAttributeName << " "
				   << _attributeType(curAttribute) << " "
				   << _attributeParameters(curAttribute)
				   << (curAttributeName != entity->attributes().back() ? endStr : "\n");
        }
        script << closingParenthesis;
    }
    script << endCommand;
	return script.str();
}

//// вернуть модель
//const Model& ScriptGenerator::model() const
//{
//    return *m_model;
//}

// возвращает sql скрипт для создание БД
std::string ScriptGenerator::generateScript(const Model& model)
{
// создать скрипт из компонентов
    std::stringstream script;
	for (const auto & curEntityName : model.entities())
    {
		script << _scriptForEntity(curEntityName, model.entity(curEntityName));
        script << "\n";
    }

    return script.str();
}

//ScriptGenerator::~ScriptGenerator()
//{
//}
