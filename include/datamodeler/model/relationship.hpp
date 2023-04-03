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
public:
    enum class RELATION_TYPE {Identifying, NonIdentifying, ManyToMany};     // типы отношений 
private:
    // std::string m_name;     // имя объекта
    Relationship::RELATION_TYPE m_type;                                     // тип отношения
    std::pair<std::string, std::string> m_entitiesPair;                 // объекты отношения
//    std::string m_name;                                                     // имя отношения
public:
    Relationship(Relationship::RELATION_TYPE, std::string entity_1, std::string entity_2, std::string name);
    const std::pair<std::string, std::string>& entitiesPair() const;
    // std::string name() const;
    ~Relationship();
};
