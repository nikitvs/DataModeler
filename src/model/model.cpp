#include <stdexcept>
#include <QDebug>
#include <QJsonArray>
#include "datamodeler/model/model.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/relationship.hpp"
#include "datamodeler/model/modelsaver.hpp"
//#include "model.hpp"
//#include "entity.hpp"
//#include "relationship.hpp"
//#include "modelsaver.hpp"

Model::Model(std::string DBMS, std::string name, QObject* parent)
    : m_DBMS(DBMS)
	, m_currentStep(0)
	, m_modelSaver(new ModelSaver)
	, ModelComponent(name, parent)
{
	QObject::connect(this, &Model::_changed, this, &Model::_saveModel);
	_saveModel();
}

void Model::_saveModel()
{
	m_modelSaver->saveJson(Model::toJson(), m_currentStep++);
}

QJsonObject Model::toJson() const
{
	QJsonObject jsonObj = ModelComponent::toJson();
	jsonObj.insert("entities", ModelComponent::toJson(m_entities));
	jsonObj.insert("relationships", ModelComponent::toJson(m_relationships));
	return jsonObj;
}

void Model::fromJson(const QJsonObject& jsonObj)
{
	QObject::disconnect(this, &Model::_changed, this, &Model::_saveModel);
	ModelComponent::_clearList(m_entities);
	ModelComponent::_clearList(m_relationships);

	setName(jsonObj.value("name").toString().toStdString());
	setmAdditionalModelParameters(jsonObj.value("additionalModelParameters").toVariant());
	for (auto const & jsonValue : jsonObj.value("entities").toArray())
	{
		addEntity(Entity::fromJson(jsonValue.toObject(), this));
	}
	for (auto const & jsonValue : jsonObj.value("relationships").toArray())
	{
		addRelationship(Relationship::fromJson(jsonValue.toObject(), this));
	}

	QObject::connect(this, &Model::_changed, this, &Model::_saveModel);
}

std::string Model::dbms() const
{
    return m_DBMS;
}

// методы добавления сущности в модель
void Model::addEntity(Entity* entity)
{
    ModelComponent::_addElement(entity, m_entities);

	QObject::connect(entity, &Entity::_changed, this, &Model::_changed);
	emit _changed();
}

// удалить сущность из модели
void Model::deleteEntity(std::string name)
{
    ModelComponent::_deleteElement(entity(name), m_entities);

	emit _changed();
}

// вернуть сущность по имени
Entity* Model::entity(std::string name) const
{
    return ModelComponent::_getElement(m_entities, name);
}

void Model::addRelationship(Relationship* relationship)
{
    ModelComponent::_addElement(relationship, m_relationships);

	QObject::connect(relationship, &Relationship::_changed, this, &Model::_changed);
	emit _changed();
}

// удалить отношение из модели
void Model::deleteRelationship(std::string name)
{
    ModelComponent::_deleteElement(relationship(name), m_relationships);

	emit _changed();
}

// вернуть отношение по имени
Relationship* Model::relationship(std::string name) const
{
    return ModelComponent::_getElement(m_relationships, name);
}

// получить список имен сущностей
std::vector<std::string> Model::entities() const
{
    return ModelComponent::_getNamesList(m_entities);
}

// получить список имен отношений
std::vector<std::string> Model::relationships() const
{
    return ModelComponent::_getNamesList(m_relationships);
}

bool Model::redo()
{
	if (m_currentStep < m_modelSaver->maxStep())
	{
		const QJsonObject loadedModel = m_modelSaver->loadJson(m_currentStep++);
		fromJson(loadedModel);
		return true;
	}
	return false;
}

bool Model::undo()
{
	if (m_currentStep > 0)
	{
		const QJsonObject loadedModel = m_modelSaver->loadJson(--m_currentStep);
		fromJson(loadedModel);
		return true;
	}
	return false;
}


// осфободить память для всех сущностей и отношений
Model::~Model()
{
    ModelComponent::_clearList(m_entities);
    ModelComponent::_clearList(m_relationships);

	delete m_modelSaver;
}
