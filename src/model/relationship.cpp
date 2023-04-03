#include "datamodeler/model/relationship.hpp"
// #include "datamodeler/model/entity.hpp"

Relationship::Relationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
    : m_type(type)
    , ModelComponent(name)
{
    m_entitiesPair.first  = entity_1;
    m_entitiesPair.second = entity_2;
}

// std::string Relationship::name() const
// {
//     return m_name;
// }

const std::pair<std::string, std::string>& Relationship::entitiesPair() const
{
    return m_entitiesPair;
}

Relationship::~Relationship()
{
}
