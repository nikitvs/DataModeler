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
//    if (attribute->primaryKey()){
//        parameters += "PRIMARY KEY";
//    } else {
        if (attribute->nullable()){
            parameters += "NULL";
        } else {
            parameters += "NOT NULL";
        };
//    }
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

	std::string endCommand		   = ";\n";
	std::string endStr			   = ",\n";
	std::string openingParenthesis = "\n(\n";
	std::string closingParenthesis = ")";

	const Entity* entity = model.entity(entityName);


	std::stringstream script;
	script << "CREATE TABLE " << entityName;

	int attributesCount = entity->attributes().size();
	if (attributesCount == 0)
	{
		for (const auto & curRelationshipName : model.relationships())
		{
			if (model.relationship(curRelationshipName)->to() == entityName)
			{
				++attributesCount;
				break;
			}
		}
	}

	// если атрибуты есть
	std::vector<std::string> primaryKeys;
	std::vector<std::pair<std::string, std::string>> foreignKeys;
	if (attributesCount > 0)
	{
		script << openingParenthesis;

		std::stringstream attributesScript;

		for (const auto & curAttributeName : entity->attributes()) {
			attributesScript << _scriptForAttribute(curAttributeName, entity->attribute(curAttributeName)) << endStr;
			if (entity->attribute(curAttributeName)->primaryKey())
			{
				primaryKeys.push_back(curAttributeName);
			}
		}

		for (const auto & curRelationshipName : model.relationships())
		{
			const Relationship* curRelationship = model.relationship(curRelationshipName);
			if (curRelationship->to() == entityName)
			{
				for (const auto & curAttributeName : model.entity(curRelationship->from())->attributes())
				{
					const Attribute* curAttribute = model.entity(curRelationship->from())->attribute(curAttributeName);
					if (curAttribute->primaryKey() && !curRelationship->isLoop())
					{
						attributesScript << _scriptForAttribute(curAttributeName,
																model.entity(curRelationship->from())->attribute(curAttributeName)) << endStr;
						foreignKeys.push_back({curAttributeName, curRelationship->from()});
						if (curRelationship->type() == Relationship::RELATION_TYPE::Identifying)
						{
							primaryKeys.push_back(curAttributeName);
						}
					}
				}
			}
		}

		std::string tmp = attributesScript.str();
		tmp.resize(tmp.size() - endStr.size());
		script << tmp << "\n";
		script << closingParenthesis;
	}
	script << endCommand;

	if (primaryKeys.size() > 0)
	{
		script << "\n" << "ALTER TABLE " << entityName << "\n"
			   << "    " << "ADD PRIMARY KEY" << " "
			   << "(";

		std::stringstream attributesScript;
		for (const auto & curAttribute : primaryKeys)
		{
			attributesScript << curAttribute << ", ";
		}
		std::string tmp = attributesScript.str();
		tmp.resize(tmp.size() - 2);
		script << tmp;
		script << ")" << ";\n";
	}


	for (const auto & curAttributePair : foreignKeys) {
		script << "\n" << "ALTER TABLE " << entityName << "\n"
			   << "    " << "ADD FOREIGN KEY" << " "
			   << "(" << curAttributePair.first << ")" << " "
			   << "REFERENCES " << curAttributePair.second
			   << "(" << curAttributePair.first << ")" << ";\n";
	}

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
