#pragma once

#include <list>
#include <string>

// объявление класса сущности
class Entity;
// объявление класса отношения
class Relationship;

class Model
{
private:
    std::list<Entity*> m_entitiesList;                      // список сущностей
    std::list<Relationship*> m_relationshipsList;           // список отношений между сущностями

public:
    Model();
    void addEntity(Entity* const);                          // добавить сущность в модель
    Entity* addEntity();
    Entity* addEntity(std::string);
    void delEntity(Entity* const);                          // удалить сущность из модели (+ связанные отношения)
    void addRelationship(Relationship* const);              // добавить отношение в модель
    void delRelationship(Relationship* const);              // удалить отношение из модели
    std::list<Entity*> entities();                          // получить список сущностей
    std::list<Relationship*> relationships();               // получить список отношений
    ~Model();
};