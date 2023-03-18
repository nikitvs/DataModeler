#include <algorithm>
#include <stdexcept>

#include "model.hpp"
#include "entity.hpp"
#include "relationship.hpp"

Model::Model()
{
}

// методы добавления сущности в модель
Entity& Model::addEntity(std::string name)
{
    // порождать исключение, когда сущность с таким именем уже есть
    if (std::find_if(m_entitiesList.begin(), m_entitiesList.end(), [name](Entity* e){return e->name() == name;}) != m_entitiesList.end())
        throw std::invalid_argument("There is already an entity with this name!"); // не уверен что сработает для последнего элемента
    

    Entity* entity = new Entity(name);
    m_entitiesList.push_back(entity);
    return *entity;
}
// дополнительный метод, как способ для параметра указать зависимое от поля класса значение по умолчанию
Entity& Model::addEntity()
{
    return addEntity("E_" + std::to_string(m_entitiesList.size() + 1));
}

// вернуть сущность по имени
Entity& Model::entity(std::string name)
{
    return *(*std::find_if(m_entitiesList.begin(), m_entitiesList.end(), [name](Entity* e){return e->name() == name;}));
}

// удалить сущность из модели (+ связанные отношения)
void Model::removeEntity(std::string name)
{
    // убрать сущность из списка
    Entity* l_entity = &entity(name);
    m_entitiesList.remove(l_entity);

    std::list<Relationship*> tmpDelRelationList; // список отношений, которые будут удалены
    // опредедлить отношения для удаления
    for(auto iter = m_relationshipsList.begin(); iter!=m_relationshipsList.end(); ++iter)
    {
        const Relationship* const currentRelationship = static_cast<Relationship*>(*iter);
        if (currentRelationship->entitiesPair().first == name || currentRelationship->entitiesPair().second == name)
            tmpDelRelationList.push_back(*iter);
    }
    // удаление отношений, связанных с сущностью
    for(auto iter = tmpDelRelationList.begin(); iter!=tmpDelRelationList.end(); ++iter)
    {
        removeRelationship(*iter);
    }
    // удалить сущность
    delete l_entity;
}

// добавить отношение в модель
Relationship& Model::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
{
    // порождать исключение, когда отношение с таким именем уже есть
    if (std::find_if(m_relationshipsList.begin(), m_relationshipsList.end(),
                    [name](Relationship* r){return r->name() == name;}) != m_relationshipsList.end())
        throw std::invalid_argument("There is already an relationship with this name!"); // не уверен что сработает для последнего элемента

    Relationship* relationship = new Relationship(type, &entity(entity_1), &entity(entity_1), name);
    m_relationshipsList.push_back(relationship);
    return *relationship;
}
// аналогичная уловка как для сущностей
Relationship& Model::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2)
{
    std::string name = std::to_string(m_relationshipsList.size() + 1);
    return addRelationship(type, entity_1, entity_2, "R_" + name);
}

// вернуть сущность по имени
Relationship& Model::relationship(std::string name)
{
    return *(*std::find_if(m_relationshipsList.begin(), m_relationshipsList.end(), [name](Relationship* r){return r->name() == name;}));
}

// удалить отношение из модели
void Model::removeRelationship(Relationship* relationship)
{
    m_relationshipsList.remove(relationship);
    delete relationship;
}
void Model::removeRelationship(std::string name)
{
    removeRelationship(*std::find_if(m_relationshipsList.begin(), m_relationshipsList.end(), 
                                     [name](Relationship* relation){return relation->name() == name;}));
}

// получить список имен сущностей
std::list<std::string> Model::entities()
{
    std::list<std::string> names;
    for (auto const& e : m_entitiesList)
    {
        names.push_back(e->name());
    }
    return names;
}
// получить список имен отношений
std::list<std::string> Model::relationships()
{
    std::list<std::string> names;
    for (auto const& r : m_relationshipsList)
    {
        names.push_back(r->name());
    }
    return names;
}

// // получить список сущностей
// std::list<Entity*> Model::entities()
// {
//     return m_entitiesList;
// }
// // получить список отношений
// std::list<Relationship*> Model::relationships()
// {
//     return m_relationshipsList;
// }

// осфободить память для всех сущностей и отношений
Model::~Model()
{
    for(auto iter = m_entitiesList.begin(); iter!=m_entitiesList.end(); ++iter)
    {
        delete *iter;
    }
    for(auto iter = m_relationshipsList.begin(); iter!=m_relationshipsList.end(); ++iter)
    {
        delete *iter;
    }
}