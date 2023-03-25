#pragma once
#include <vector>
#include "entity.hpp"
#include "relationship.hpp"
#include "_modelComponent.hpp"

// класс модели БД
class Model : public ModelComponent
{
private:
    std::list<Entity*> m_entitiesList;                      // список сущностей
    std::list<Relationship*> m_relationshipsList;           // список отношений между сущностями
    std::string m_DBMS;

public:
    Model(std::string DBMS, std::string name = "");
    std::string dbms() const;
    Entity& addEntity(std::string name = "");                       // добавить сущность в модель
    Entity& entity(std::string name) const;                         // получить сущность
    void removeEntity(std::string name);                            // удалить сущность из модели (+ связанные отношения)
    Relationship& addRelationship(Relationship::RELATION_TYPE type, // добавить отношение в модель
                         std::string entity_1, 
                         std::string entity_2,
                         std::string name = "");
    Relationship& relationship(std::string name) const;                // получить сущность
//    void removeRelationship(Relationship*);                          // удалить отношение из модели
    void removeRelationship(std::string name);
    std::vector<std::string> entities() const;                         // получить список имен сущностей
    std::vector<std::string> relationships() const;                    // получить список имен отношений
    ~Model();
};
