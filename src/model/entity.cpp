#include "entity.hpp"

Entity::Entity()
{
}

Entity::Entity(std::string name)
    :   m_name(name)
{
}

std::string Entity::name() const
{
    return m_name;
}

Entity::~Entity()
{
}
