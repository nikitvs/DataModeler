#include "datamodeler/modeleditor.hpp"
#include "datamodeler/config.hpp"

ModelEditor::ModelEditor(Model &model) : m_model(model)
{
	Config::initTypes("./types.json");
}

// проверить есть ли объект с таким именем
bool ModelEditor::_existObject(const std::vector<std::string> &namesVector, const std::string name)
{
	if (std::find_if(namesVector.begin(), namesVector.end(), [name](std::string currentName)
					 { return currentName == name; }) != namesVector.end())
	{
		return true;
	}
	else
	{
		return false;
	}
};

// сгенерировать имя для объекта
std::string ModelEditor::_generateObjectName(const std::vector<std::string> &namesVector, const std::string name, const std::string baseName)
{
	std::string objectName;
	// если имя пустое - сгенерировать имя
	if (name.empty())
	{
		int index = namesVector.size() + 1;
		// если уже есть элемент с таким именем, инкрементировать индекс
		while (std::find_if(namesVector.begin(), namesVector.end(), [=](std::string currentName)
							{ return (baseName + std::to_string(index) == currentName); }) != namesVector.end())
		{
			++index;
		}
		// имя как базовое имя + индекс
		objectName = baseName + std::to_string(index);
	}
	else
	{
		// если не пустое, задать
		objectName = name;
	}
	return objectName;
}

void ModelEditor::_throwElementNotExist(const std::vector<std::string> &namesVector, const std::string name)
{
	if (!(_existObject(namesVector, name)))
	{
		std::stringstream ss;
		ss << "There is no an element with name: "
		   << "\"" << name << "\""
		   << "!";
		throw std::invalid_argument(ss.str());
	}
}

void ModelEditor::_throwElementExist(const std::vector<std::string> &namesVector, const std::string name)
{
	if (_existObject(namesVector, name))
	{
		std::stringstream ss;
		ss << "There is already an element with name: "
		   << "\"" << name << "\""
		   << "!";
		throw std::invalid_argument(ss.str());
	}
}

// Entity* ModelEditor::_entity(std::string name) const
// {
// 	const auto list = m_model.entities();
// 	return *std::find_if(list.begin(), list.end(), [name](Entity* elem){return elem->name() == name;});
// }

// Relationship* ModelEditor::_relationship(std::string name) const
// {
// 	const auto list = m_model.relationships();
// 	return *std::find_if(list.begin(), list.end(), [name](Relationship* elem){return elem->name() == name;});
// }

// --- Config ---
std::vector<std::string> ModelEditor::availableDBMS()
{
	return Config::availableDBMS();
}

std::vector<std::string> ModelEditor::availableDomains(std::string DBMS)
{
	return Config::availableDomains(DBMS);
}

std::vector<std::string> ModelEditor::availableTypes(std::string DBMS, std::string domain)
{
	return Config::availableTypes(DBMS, domain);
}

std::string ModelEditor::modelDbms() const
{
	return m_model.dbms();
}

std::vector<std::string> ModelEditor::entities() const
{
	return m_model.entities();
}

std::vector<std::string> ModelEditor::relationships() const
{
	return m_model.relationships();
}

void ModelEditor::addEntity(std::string name)
{
	// проверить или создать имя
	std::string entityName = _generateObjectName(entities(), name, "E_");
	_throwElementExist(entities(), entityName);

	m_model.addEntity(new Entity(entityName));
}

void ModelEditor::deleteEntity(std::string name)
{
	_throwElementNotExist(entities(), name);
	m_model.deleteEntity(name);

    // удаление отношений, связанных с сущностью
	for(const auto & relationshipName : relationships())
    {
		auto currentEntitiesPair = m_model.relationship(relationshipName)->entitiesPair();
        if (currentEntitiesPair.first == name || currentEntitiesPair.second == name)
            deleteRelationship(relationshipName);
    }
}

void ModelEditor::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
{
	// задать имя отношению
	std::string relationshipName = _generateObjectName(relationships(), name, "R_" + entity_1 + entity_2);

	_throwElementNotExist(entities(), entity_1);
	_throwElementNotExist(entities(), entity_2);
	_throwElementExist(relationships(), relationshipName);

	/*if (type == Relationship::RELATION_TYPE::Identifying && entity_1 == entity_2)
	{
		throw
	}*/
	
	m_model.addRelationship(new Relationship(type, entity_1, entity_2, relationshipName));
}

void ModelEditor::deleteRelationship(std::string name)
{
	_throwElementNotExist(relationships(), name);
	m_model.deleteRelationship(name);
}

void ModelEditor::addAttrubute(std::string entityName, std::string typeDomain, std::string type, std::string name)
{
	// сущность для добавления атрибута
	_throwElementNotExist(entities(), entityName);
	Entity *entity = m_model.entity(entityName);
	// задать имя атрибуту
	std::string attributeName = _generateObjectName(entity->attributes(), name, typeDomain + "_");
	_throwElementExist(entity->attributes(), attributeName);

	entity->addAttribute(new Attribute(typeDomain, attributeName, type, Config::typeParmetersTemplate(modelDbms(), typeDomain, type)));
}

void ModelEditor::deleteAttrubute(std::string entityName, std::string attributeName)
{
	_throwElementNotExist(entities(), entityName);
	Entity *entity = m_model.entity(entityName);

	_throwElementNotExist(entity->attributes(), attributeName);
	entity->deleteAttribute(attributeName);
}



ModelEditor::~ModelEditor()
{
}
