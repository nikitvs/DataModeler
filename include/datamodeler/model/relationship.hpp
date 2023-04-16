#pragma once

#include "_modelComponent.hpp"

// объявление класса сущности
class Entity;

// класс отношений между сущностями
class Relationship : public ModelComponent
{
	Q_OBJECT
public:
	enum class RELATION_TYPE {Identifying, NonIdentifying, ManyToMany};     // доступные типы отношений

private:
    Relationship::RELATION_TYPE m_type;                                     // тип отношения
	std::pair<std::string, std::string> m_entitiesPair;						// объекты отношения (порядок важен)

	static std::string _enumToString(Relationship::RELATION_TYPE type);		// преобразует enum в строку
	static Relationship::RELATION_TYPE _stringToEnum(std::string type);		// преобразует строку в enum

public:
	Relationship(Relationship::RELATION_TYPE type,
				 std::pair<std::string, std::string> entitiesPair,
				 QObject* parent = nullptr);								// задается тип и объекты отношения
	const std::pair<std::string, std::string>& entitiesPair() const;		// получить объекты отношения
	bool setEntitiesPair(std::string entity_1, std::string entity_2);		// задать объекты отношения
	bool isLoop() const;													// отношение сущности самой на себя?
	Relationship::RELATION_TYPE type() const;								// получить тип отношения
	bool setType(Relationship::RELATION_TYPE type);							// задать ти отношения
	QJsonObject toJson() const override;									// получить json объект для отношения
	static Relationship* fromJson(const QJsonObject& jsonObj,
								  QObject* parent = nullptr);				// получить объект отношения из json
    ~Relationship();
};
