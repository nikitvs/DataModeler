#include "datamodeler/model/attribute.hpp"

Attribute::Attribute(std::string typeDomain, std::string name)
    : m_typeDomain(typeDomain)
    , ModelComponent(name)
{
}

void Attribute::setType(std::string type)
{
    m_type = type;
}

std::string Attribute::type() const
{
    return m_type;
}

void Attribute::setTypeDomain(std::string typeDomain)
{
    m_typeDomain = typeDomain;
}

std::string Attribute::typeDomain() const
{
    return m_typeDomain;
}

int Attribute::length() const
{
    return m_length;
}

void Attribute::setLength(int length)
{
    m_length = length;
}

// задает флаг допустимости null
bool Attribute::setNullable(bool nullable)
{
    // если стоит первичный ключ - этот флаг менять нельзя
    if (m_primaryKey)
        return false;

    m_nullable = nullable;
    return true;
}

bool Attribute::nullable() const
{
    return m_nullable;
}

// задает флаг первичный ключ
void Attribute::setPrimaryKey(bool primaryKey)
{
    if(primaryKey)
        m_nullable = false;
    m_primaryKey = primaryKey;
}

bool Attribute::primaryKey() const
{
    return m_primaryKey;
}

Attribute::~Attribute()
{
};
