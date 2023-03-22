#include "entity.hpp"

Entity::Entity(std::string name) : ModelComponent(name)
{
}

//std::string Entity::name() const
//{
//    return m_name;
//}

Attribute& Entity::addAttribute(std::string typeDomain, std::string name)
{
    // если пользователь не задал имя
    if (name.empty())
        return addAttribute(typeDomain, _genBaseName(m_attributes, typeDomain + "_"));
    // порождать исключение, когда сущность с таким именем уже есть
    _checkName(m_attributes, name);


    Attribute* attribute = new Attribute(typeDomain, name);
    m_attributes.push_back(attribute);
    return *attribute;
}

Entity::~Entity()
{
}
