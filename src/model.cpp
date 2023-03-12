#include "model.hpp"
#include "modelComponents/relationship.hpp"

Model::Model()
{
}

// добавить сущность в модель
void Model::addEntity(Entity* const entity)
{
    m_entitiesList.push_back(entity);
}

// удалить сущность из модели (+ связанные отношения)
void Model::delEntity(Entity* const entity)
{
    // удалить сущность
    m_entitiesList.remove(entity);

    std::list<Relationship*> tmpDelRelationList; // список отношений, которые будут удалены
    // опредедлить отношения для удаления
    for(auto iter = m_relationshipsList.begin(); iter!=m_relationshipsList.end(); ++iter)
    {
        Relationship* const currentRelationship = static_cast<Relationship*>(*iter);
        if (currentRelationship->getEntitiesPair().first == entity || currentRelationship->getEntitiesPair().second == entity)
        {
            tmpDelRelationList.push_back(*iter);
        }
    }
    // удаление отношений, связанных с сущностью
    for(auto iter = tmpDelRelationList.begin(); iter!=tmpDelRelationList.end(); ++iter)
    {
        delRelationship(*iter);
    }
}

// добавить отношение в модель
void Model::addRelationship(Relationship* const relationship)
{
    m_relationshipsList.push_back(relationship);
}

// удалить отношение из модели
void Model::delRelationship(Relationship* const relationship)
{
    m_relationshipsList.remove(relationship);
}

// получить список сущностей
const std::list<Entity*> Model::entities()
{
    return m_entitiesList;
}
// получить список отношений
const std::list<Relationship*> Model::relationships()
{
    return m_relationshipsList;
}

Model::~Model()
{
}