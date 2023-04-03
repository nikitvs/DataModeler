#include <stdexcept>
#include "datamodeler/model/model.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/relationship.hpp"

Model::Model(std::string DBMS, std::string name)
    : m_DBMS(DBMS)
    , ModelComponent(name)
{
}

// std::string Model::name() const
// {
//     return m_name;
// }

std::string Model::dbms() const
{
    return m_DBMS;
}

// методы добавления сущности в модель
void Model::addEntity(Entity* entity)
{
    ModelComponent::_addElement(entity, m_entities);
}

// удалить сущность из модели
void Model::deleteEntity(std::string name)
{
    ModelComponent::_deleteElement(entity(name), m_entities);
}

// вернуть сущность по имени
Entity* Model::entity(std::string name) const
{
    return ModelComponent::_getElement(m_entities, name);
}

void Model::addRelationship(Relationship* relationship)
{
    ModelComponent::_addElement(relationship, m_relationships);
}

// удалить отношение из модели
void Model::deleteRelationship(std::string name)
{
    ModelComponent::_deleteElement(relationship(name), m_relationships);
}

// вернуть отношение по имени
Relationship* Model::relationship(std::string name) const
{
    return ModelComponent::_getElement(m_relationships, name);
}

// получить список имен сущностей
std::vector<std::string> Model::entities() const
{
    return ModelComponent::_getNamesList(m_entities);
}

// получить список имен отношений
std::vector<std::string> Model::relationships() const
{
    return ModelComponent::_getNamesList(m_relationships);
}

// осфободить память для всех сущностей и отношений
Model::~Model()
{
    ModelComponent::_clearList(m_entities);
    ModelComponent::_clearList(m_relationships);
}