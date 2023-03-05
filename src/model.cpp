#include "model.hpp"

Model::Model(Model::DATABASE_TYPE type)
    : m_databaseType(type)
{
}

// Model::databaseType Model::getDatabaseType()
// {
//     return m_databaseType;
// }

// void Model::addEntity(const Entity* entity)
// {
//     m_entitiesList.push_back(entity);
// }

Model::~Model()
{
}
