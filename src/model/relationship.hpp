#pragma once

#include <list>
#include <string>

// объявление класса сущности
class Entity;

// класс отношений между сущностями
class Relationship
{
public:
    enum RELATION_TYPE {Identifying, NonIdentifying, ManyToMany};   // типы отношений 
private:
    Relationship::RELATION_TYPE m_type;                             // тип отношения
    std::pair<const Entity*, const Entity*> m_entitiesPair;         // объекты отношения
    std::string m_name;                                             // имя отношения
public:
    Relationship(Relationship::RELATION_TYPE, const Entity*, const Entity*, std::string name);
    std::pair<std::string, std::string> entitiesPair() const;
    std::string name() const;
    ~Relationship();
};
