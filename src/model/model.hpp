#pragma once

#include <list>
#include <string>

#include "relationship.hpp"

// объявление класса сущности
class Entity;
// объявление класса отношения
class Relationship;

// класс модели БД
class Model
{
private:
    std::list<Entity*> m_entitiesList;                      // список сущностей
    std::list<Relationship*> m_relationshipsList;           // список отношений между сущностями

public:
    Model();
    Entity& addEntity();                                            // добавить сущность в модель
    Entity& addEntity(std::string name);
    Entity& entity(std::string name);                               // получить сущность
    void removeEntity(std::string name);                            // удалить сущность из модели (+ связанные отношения)
    Relationship& addRelationship(Relationship::RELATION_TYPE type, // добавить отношение в модель
                         std::string entity_1, 
                         std::string entity_2,
                         std::string name);
    Relationship& addRelationship(Relationship::RELATION_TYPE type,
                         std::string entity_1, 
                         std::string entity_2);
    Relationship& relationship(std::string name);                   // получить сущность
    void removeRelationship(Relationship*);                         // удалить отношение из модели
    void removeRelationship(std::string name);
    std::list<std::string> entities();                              // получить список имен сущностей
    std::list<std::string> relationships();                         // получить список имен отношений
    // std::list<Entity*> entities();                                  // получить список сущностей
    // std::list<Relationship*> relationships();                       // получить список отношений
    ~Model();
};