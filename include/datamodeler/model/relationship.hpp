#pragma once

#include <list>
#include <string>
// #include "_modelComponent.hpp"
#include "../src/model/_modelComponent.hpp"

// объявление класса сущности
class Entity;

// класс отношений между сущностями
class Relationship : public ModelComponent
{
	Q_OBJECT
public:
    enum class RELATION_TYPE {Identifying, NonIdentifying, ManyToMany};     // типы отношений 
private:
    // std::string m_name;     // имя объекта
    Relationship::RELATION_TYPE m_type;                                     // тип отношения
    std::pair<std::string, std::string> m_entitiesPair;                 // объекты отношения
//    std::string m_name;                                                     // имя отношения
private:
	static std::string _enumToString(Relationship::RELATION_TYPE type);
	static Relationship::RELATION_TYPE _stringToEnum(std::string type);
public:
	Relationship(Relationship::RELATION_TYPE,
				 std::string entity_1,
				 std::string entity_2,
				 std::string name,
				 QObject* parent = nullptr);
    const std::pair<std::string, std::string>& entitiesPair() const;
	bool setEntitiesPair(std::string entity_1, std::string entity_2);
    bool isLoop() const;
	Relationship::RELATION_TYPE type() const;
	bool setType(Relationship::RELATION_TYPE type);
	QJsonObject toJson() const override;
	static Relationship* fromJson(const QJsonObject& jsonObj, QObject* parent = nullptr);
    // std::string name() const;
    ~Relationship();
};
