#include "relationship.hpp"

Relationship::Relationship(Relationship::RELATION_TYPE type, const Entity* entity_1, const Entity* entity_2)
    :   m_type(type)
{
    m_entitiesPair.first  = entity_1;
    m_entitiesPair.second = entity_2;
}

const std::pair<const Entity*, const Entity*> Relationship::getEntitiesPair() const
{
    return m_entitiesPair;
}

Relationship::~Relationship()
{
}
