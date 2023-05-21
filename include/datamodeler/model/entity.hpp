#pragma once

#include "_modelComponent.hpp"

class Attribute;

// класс сущности
class Entity : public ModelComponent
{
	Q_OBJECT
private:
	std::vector<std::pair<std::string, Attribute*>> m_attributes;		// вектор атрибутов сущности

public:
	Entity(QObject* parent = nullptr);									// конструктор
	void addAttribute(Attribute* attribute, std::string name = "");		// добавить атрибут
	void deleteAttribute(std::string name);								// удалить атрибут
	void renameAttribute(std::string oldName, std::string newName);		// переименовать атрибут
	Attribute* attribute(std::string name) const;						// получить атрибут по указателю
	std::string attributeName(const Attribute* attribute) const;		// получить имя атрибута
	std::vector<std::string> attributes() const;						// получить вектор имен атрибутов
	QJsonObject toJson() const override;								// получить json строку для объекта сущности
	static Entity* fromJson(const QJsonObject& jsonObj,
							QObject* parent = nullptr);					// получить объект сущности из json строки
	~Entity();
};
