#include <stdexcept>
#include <fstream>
#include "datamodeler/model/model.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/relationship.hpp"
#include "modelsaver.hpp"
#include "QJsonDocument"

Model::Model(std::string DBMS, QObject* parent)
	: m_DBMS(DBMS)
	, m_currentStep(0)
	, m_modelSaver(new ModelSaver)
	, ModelComponent(parent)
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
	jsonObj.insert("dbms", QString::fromStdString(m_DBMS));
	jsonObj.insert("entities", ModelComponent::toJson(m_entities));
	jsonObj.insert("relationships", ModelComponent::toJson(m_relationships));
	return jsonObj;
}

void Model::save(std::string fileFullName) const
{
	std::ofstream fout(fileFullName);
	if (fout.is_open())
	{
		fout << QString(QJsonDocument(toJson()).toJson(QJsonDocument::Compact)).toStdString();
		fout.close();
	} else
	{
		throw std::invalid_argument(QString("Файл с именем %1 невозможно открыть").
									arg(QString::fromStdString(fileFullName)).toStdString());
	}
}

Model* Model::load(std::string fileFullName)
{
	Model* model = new Model("");
	std::ifstream fin(fileFullName);
	if (fin.is_open())
	{
		std::string json;
		std::getline(fin, json);
		model->fromJson(QJsonDocument::fromJson(QByteArray::fromStdString(json)).object());
		fin.close();
		emit model->_changed();
	} else
	{
		throw std::invalid_argument(QString("Файл с именем %1 невозможно открыть").
									arg(QString::fromStdString(fileFullName)).toStdString());
	}
	return model;
}

void Model::fromJson(const QJsonObject& jsonObj)
{
	QObject::disconnect(this, &Model::_changed, this, &Model::_saveModel);

	ModelComponent::_clearMap(m_entities);
	ModelComponent::_clearMap(m_relationships);

	ModelComponent::fromJson<Model>(jsonObj, this);

	m_DBMS = jsonObj.value("dbms").toString().toStdString();

	QJsonArray entitiesArr = jsonObj.value("entities").toArray();
	for (QJsonArray::iterator it = entitiesArr.begin(); it != entitiesArr.end(); ++it)
	{
		addEntity(Entity::fromJson((*it).toObject(), this), Entity::nameFromJson((*it).toObject()));
	}
	QJsonArray relationshipsArr = jsonObj.value("relationships").toArray();
	for (QJsonArray::iterator it = relationshipsArr.begin(); it != relationshipsArr.end(); ++it)
	{
		addRelationship(Relationship::fromJson((*it).toObject(), this), Relationship::nameFromJson((*it).toObject()));
	}

	QObject::connect(this, &Model::_changed, this, &Model::_saveModel);
}

std::string Model::dbms() const
{
	return m_DBMS;
}

// методы добавления сущности в модель
void Model::addEntity(Entity* entity, std::string name)
{
	if (name.empty()) name = _generateObjectName("E_", m_entities);
	ModelComponent::_addElement(name, entity, m_entities);
	QObject::connect(entity, &Entity::_changed, this, &Model::_changed);
}

// удалить сущность из модели
void Model::deleteEntity(std::string name)
{
	return ModelComponent::_deleteElement(name, m_entities);
}

void Model::renameEntity(std::string oldName, std::string newName)
{
	return ModelComponent::_renameElement(oldName, newName, m_entities);
}

// вернуть сущность по имени
Entity* Model::entity(std::string name) const
{
	return ModelComponent::_getElement(name, m_entities);
}

std::string Model::entityName(const Entity* entity) const
{
	return ModelComponent::_getElement(entity, m_entities);
}

void Model::addRelationship(Relationship* relationship, std::string name)
{
	if (relationship->isLoop() && relationship->type() == Relationship::RELATION_TYPE::Identifying)
	{
		throw std::invalid_argument(QString("Нельзя добавить в модель цикличную идентифицирующую связь %1").
									arg(QString::fromStdString(name)).toStdString());
	} else if (!entity(relationship->from()) || !entity(relationship->to()))
	{
		throw std::invalid_argument(QString("Нельзя добавить в модель связь %1 для несуществующих сущностей").
									arg(QString::fromStdString(name)).toStdString());
	}

	if (name.empty()) name = _generateObjectName("R_", m_relationships);
	ModelComponent::_addElement(name, relationship, m_relationships);
	QObject::connect(relationship, &Relationship::_changed, this, &Model::_changed);
}

// удалить отношение из модели
void Model::deleteRelationship(std::string name)
{
	return ModelComponent::_deleteElement(name, m_relationships);
}

void Model::renameRelationship(std::string oldName, std::string newName)
{
	return ModelComponent::_renameElement(oldName, newName, m_relationships);
}

// вернуть отношение по имени
Relationship* Model::relationship(std::string name) const
{
	return ModelComponent::_getElement(name, m_relationships);
}

std::string Model::relationshipName(const Relationship* relationship) const
{
	return ModelComponent::_getElement(relationship, m_relationships);
}

// получить список имен сущностей
std::vector<std::string> Model::entities() const
{
	return ModelComponent::_getNamesVector(m_entities);
}

// получить список имен отношений
std::vector<std::string> Model::relationships() const
{
	return ModelComponent::_getNamesVector(m_relationships);
}

bool Model::redo()
{
	if (m_currentStep < m_modelSaver->maxStep())
	{
		const QJsonObject loadedModel = m_modelSaver->loadJson(++m_currentStep);
		fromJson(loadedModel);
		return true;
	}
	return false;
}

bool Model::undo()
{
	if (m_currentStep > 1)
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
	ModelComponent::_clearMap(m_entities);
	ModelComponent::_clearMap(m_relationships);

	delete m_modelSaver;
}
