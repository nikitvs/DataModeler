#pragma once
#include <list>
#include "../src/model/_modelComponent.hpp"

class Entity;
class Relationship;

// класс модели БД
class Model : public ModelComponent
{
private:
    // std::string m_name;     // имя объекта
    std::list<Entity*> m_entities;                      // список сущностей
    std::list<Relationship*> m_relationships;           // список отношений между сущностями
    std::string m_DBMS;

public:
    Model(std::string DBMS, std::string name);
    std::string dbms() const;
    // std::string name() const;
    void addEntity(Entity* entity);                       // добавить сущность в модель
    void deleteEntity(std::string name);                            // удалить сущность из модели (+ связанные отношения)
    Entity* entity(std::string name) const;                         // получить сущность
    void addRelationship(Relationship* relationship); // добавить отношение в модель
    void deleteRelationship(std::string name);   
    Relationship* relationship(std::string name) const;                // получить сущность              // получить сущность
    std::vector<std::string> entities() const;
    std::vector<std::string> relationships() const;                     // получить список имен сущностей
    // const std::list<Relationship*>& relationships() const;                    // получить список имен отношений
    ~Model();
};
