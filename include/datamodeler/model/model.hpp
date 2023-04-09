#pragma once
#include <list>
#include <QJsonObject>
#include "../src/model/_modelComponent.hpp"

class Entity;
class Relationship;
class ModelSaver;

// класс модели БД
class Model : public ModelComponent
{
	Q_OBJECT
private:
    std::list<Entity*> m_entities;                      // список сущностей
    std::list<Relationship*> m_relationships;           // список отношений между сущностями
    std::string m_DBMS;
	int m_currentStep;
	ModelSaver* m_modelSaver;

//private:
//	void fromJson();

private slots:
	void _saveModel();

private:
	void fromJson(const QJsonObject& jsonObj);

public:
	Model(std::string DBMS, std::string name, QObject* parent = nullptr);
	std::string dbms() const;
    void addEntity(Entity* entity);                       // добавить сущность в модель
    void deleteEntity(std::string name);                            // удалить сущность из модели (+ связанные отношения)
    Entity* entity(std::string name) const;                         // получить сущность
    void addRelationship(Relationship* relationship); // добавить отношение в модель
    void deleteRelationship(std::string name);   
    Relationship* relationship(std::string name) const;                // получить сущность              // получить сущность
    std::vector<std::string> entities() const;
	std::vector<std::string> relationships() const;                     // получить список имен сущностей
	bool redo();
	bool undo();
	QJsonObject toJson() const override;
    ~Model();
};
