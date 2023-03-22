#include "attribute.hpp"

Attribute::Attribute(std::string typeDomain, std::string name)
    : m_typeDomain(typeDomain)
    , ModelComponent(name)
{
}

Attribute::~Attribute()
{
};
