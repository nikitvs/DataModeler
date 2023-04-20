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

std::string ScriptGenerator::_scriptForAttribute(const std::string& attributeName, const Attribute* const attribute)
{
	std::string tab = "    ";

	std::stringstream script;
	script << tab
		   << attributeName << " "
		   << _attributeType(attribute) << " "
		   << _attributeParameters(attribute);
	return script.str();
}

std::string ScriptGenerator::_scriptForEntity(const std::string& entityName,
											  const Model& model)
{
	const Entity* entity = model.entity(entityName);

	std::vector<std::string> primaryKeysNames;
	std::vector<std::string> simpleAttributesNames;
	for (const auto & curAttributeName : entity->attributes()) {
		if (entity->attribute(curAttributeName)->primaryKey()) {
			primaryKeysNames.push_back(curAttributeName);
		} else {
			simpleAttributesNames.push_back(curAttributeName);
		}
	}

	std::vector<std::pair<std::string, Attribute*>> primaryForeignKeys;
	std::vector<std::pair<std::string, Attribute*>> foreignKeys;
	for (const auto & curRelationName : model.relationships()) {
		const Relationship* curRelationship = model.relationship(curRelationName);
		if (curRelationship->to() == entityName) {
			for (const auto & curAttributeName : model.entity(curRelationship->from())->attributes())
			{
				const Attribute* curAttribute = model.entity(curRelationship->from())->attribute(curAttributeName);
				if (curAttribute->primaryKey()) {
					if (curRelationship->type() == Relationship::RELATION_TYPE::Identifying) {
						primaryForeignKeys.push_back({curAttributeName,
													  model.entity(curRelationship->from())->attribute(curAttributeName)});
					} else if (curRelationship->type() == Relationship::RELATION_TYPE::NonIdentifying &&
							   !curRelationship->isLoop()) {
						foreignKeys.push_back({curAttributeName,
											   model.entity(curRelationship->from())->attribute(curAttributeName)});
					}
				}
			}

		}
	}


	std::string endCommand		   = ";\n";
	std::string endStr			   = ",\n";
	std::string openingParenthesis = "\n(\n";
	std::string closingParenthesis = ")";

	std::stringstream script;
	script << "CREATE TABLE " << entityName;

    // если атрибуты есть
	int attributesCount = primaryKeysNames.size() + primaryForeignKeys.size() +
						  foreignKeys.size()      + simpleAttributesNames.size();
	if (attributesCount > 0)
	{
        script << openingParenthesis;

		std::stringstream attributesScript;
		for (const auto & curAttributeName : primaryKeysNames) {
			attributesScript << _scriptForAttribute(curAttributeName, entity->attribute(curAttributeName)) << endStr;
		}
		for (const auto & curAttributePair : primaryForeignKeys) {
			attributesScript << _scriptForAttribute(curAttributePair.first, curAttributePair.second) << endStr;
		}
		for (const auto & curAttributePair : foreignKeys) {
			attributesScript << _scriptForAttribute(curAttributePair.first, curAttributePair.second) << endStr;
		}
		for (const auto & curAttributeName : simpleAttributesNames) {
			attributesScript << _scriptForAttribute(curAttributeName, entity->attribute(curAttributeName)) << endStr;
		}

		std::string tmp = attributesScript.str();
		tmp.resize(tmp.size() - endStr.size());
		script << tmp << "\n";
        script << closingParenthesis;
    }

//	if (primaryForeignKeys.size() + primaryForeignKeys.size() > 0)
//	{
//		script << "ALTER TABLE " << entityName << "\n";
//		for (const auto & curAttributePair : foreignKeys) {
//			script << "    " << "ADD FOREIGN KEY" << " "
//				   << "(" << curAttributePair.first << ")" << " "
//				   << "REFERENCES " << ;
//	}

    script << endCommand;
	return script.str();
}

std::list<std::string> ScriptGenerator::problemsReadyList(const Model& model)
{
	std::list<std::string> problemsList;
	for (const auto & entityName : model.entities())
	{
		Entity* entity = model.entity(entityName);
		for (const auto & attributeName : entity->attributes())
		{
			Attribute* attribute = entity->attribute(attributeName);
			if (attribute->type().empty())
			{
				problemsList.push_back(QString("Не задан тип данных для атрибута %1 сущности %2").
									   arg(QString::fromStdString(attributeName),
										   QString::fromStdString(entityName)).
									   toStdString());
			}
		}
	}
	for (const auto & relationName : model.relationships())
	{
		Relationship* relationship = model.relationship(relationName);
		if (relationship->type() == Relationship::RELATION_TYPE::ManyToMany)
		{
			problemsList.push_back(QString("Не разрешено отношение manyToMany с именем %1 для сущностей %2 и %3").
								   arg(QString::fromStdString(relationName),
									   QString::fromStdString(relationship->entitiesPair().first),
									   QString::fromStdString(relationship->entitiesPair().second)).
								   toStdString());
		}
	}
	return problemsList;
}

// возвращает sql скрипт для создание БД
std::string ScriptGenerator::generateScript(const Model& model)
{
	if (!problemsReadyList(model).empty())
	{
		throw std::invalid_argument("Модель не готова к формированию скрипта");
	}

// создать скрипт из компонентов
    std::stringstream script;
	for (const auto & curEntityName : model.entities())
    {
		script << _scriptForEntity(curEntityName, model);
        script << "\n";
    }

    return script.str();
}
