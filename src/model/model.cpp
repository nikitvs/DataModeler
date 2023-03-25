#include <stdexcept>
#include "datamodeler/model/model.hpp"

Model::Model(std::string DBMS, std::string name)
    : m_DBMS(DBMS)
    , ModelComponent(name)
{
}

std::string Model::dbms() const
{
    return m_DBMS;
}

// методы добавления сущности в модель
Entity& Model::addEntity(std::string name)
{
    // если пользователь не задал имя
    if (name.empty())
        return addEntity(_genBaseName(m_entitiesList, "E_"));
    // порождать исключение, когда сущность с таким именем уже есть
    _checkName(m_entitiesList, name);
    

    Entity* entity = new Entity(name);
    m_entitiesList.push_back(entity);
    return *entity;
}

// вернуть сущность по имени
Entity& Model::entity(std::string name) const
{
    return _getElement(m_entitiesList, name);
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
        removeRelationship((*iter)->name());
    }
    // удалить сущность
    delete l_entity;
}

// добавить отношение в модель
Relationship& Model::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
{
    // если пользователь не задал имя
    if (name.empty())
        return addRelationship(type, entity_1, entity_2, _genBaseName(m_relationshipsList, "R_"));

    // порождать исключение, когда отношение с таким именем уже есть
    _checkName(m_relationshipsList, name);

    // entity(entity_1).name() - проверка что такая сущность есть
    Relationship* relationship = new Relationship(type, entity(entity_1).name(), entity(entity_2).name(), name);
    m_relationshipsList.push_back(relationship);
    return *relationship;
}

// вернуть отношение по имени
Relationship& Model::relationship(std::string name) const
{
    return _getElement(m_relationshipsList, name);
}

// удалить отношение из модели
void Model::removeRelationship(std::string name)
{
    Relationship* r = &relationship(name);
    m_relationshipsList.remove(r);
    delete r;
}

// получить список имен сущностей
std::vector<std::string> Model::entities() const
{
    std::vector<std::string> names;
    for (auto const& e : m_entitiesList)
    {
        names.push_back(e->name());
    }
    return names;
}
// получить список имен отношений
std::vector<std::string> Model::relationships() const
{
    std::vector<std::string> names;
    for (auto const& r : m_relationshipsList)
    {
        names.push_back(r->name());
    }
    return names;
}

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
