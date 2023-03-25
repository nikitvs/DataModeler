#include "datamodeler/model/relationship.hpp"
#include "datamodeler/model/entity.hpp"

Relationship::Relationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
    : ModelComponent(name)
    , m_type(type)
{
    m_entitiesPair.first  = entity_1;
    m_entitiesPair.second = entity_2;
}

std::pair<std::string, std::string> Relationship::entitiesPair() const
{
    // return std::pair<std::string, std::string>(m_entitiesPair.first->name(), m_entitiesPair.second->name());
    return m_entitiesPair;
}

//std::string Relationship::name() const
//{
//    return m_name;
//}

Relationship::~Relationship()
{
}
