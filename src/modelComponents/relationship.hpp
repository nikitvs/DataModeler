#pragma once

#include <list>

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
public:
    std::pair<const Entity*, const Entity*> getEntitiesPair() const;
    Relationship(Relationship::RELATION_TYPE, const Entity*, const Entity*);
    ~Relationship();
};
