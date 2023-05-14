#pragma once

#include "_modelComponent.hpp"

// объявление классов модели
class Entity;
class Relationship;
class ModelSaver;

// класс модели БД
class Model : public ModelComponent
{
	Q_OBJECT
private:
	std::vector<std::pair<std::string, Entity*>> m_entities;				// вектор сущностей
	std::vector<std::pair<std::string, Relationship*>> m_relationships;     // вектор отношений между сущностями
	std::string m_DBMS;														// СУБД
	int m_currentStep;														// текущий шаг модели
	ModelSaver* m_modelSaver;												// инструмент сохранения состояний модели

	void fromJson(const QJsonObject& jsonObj);		//восстановить модель из json строки

private slots:
	void _saveModel();								// сохраняет текущее состояние модели

public:
	Model(std::string DBMS, QObject* parent = nullptr);							// конструктор (задается СУБД)
	std::string dbms() const;													// получить СУБД
	void addEntity(Entity* entity, std::string name = "");						// добавить сущность
	void deleteEntity(std::string name);										// удалить сущность
	void renameEntity(std::string oldName, std::string newName);				// переимновать сущность
	Entity* entity(std::string name) const;										// получить сущность
	std::string entityName(const Entity* entity) const;							// получить имя сущности
	std::vector<std::string> entities() const;									// получить список имен сущностей
	void addRelationship(Relationship* relationship, std::string name = "");	// добавить отношение
	void deleteRelationship(std::string name);									// удалить отношение
	void renameRelationship(std::string oldName, std::string newName);			// переимновать отношение
	Relationship* relationship(std::string name) const;							// получить отношение
	std::string relationshipName(const Relationship* relationship) const;		// получить имя отношения
	std::vector<std::string> relationships() const;								// получить список имен отношений
	bool undo();							// вернуться на шаг назад (максимум до 1-го)
	bool redo();							// повторить шаг (максимум до последнего)
	QJsonObject toJson() const override;	// получить json объект из объекта модели
	void save(std::string fileFullName) const; //сохраняет модель в файл
	static Model* load(std::string fileFullName); //загружает модель из файла (репозиторий перезаписывается!!!!!)
    ~Model();
};
