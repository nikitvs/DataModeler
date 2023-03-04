#include "model.hpp"

Model::Model(Model::databaseType)
{
}

Model::databaseType Model::getDatabaseType()
{
    return m_databaseType;
}

void Model::addEntity(const Entity& entity)
{
    m_entityList.push_back(entity);
}

Model::~Model()
{
}
