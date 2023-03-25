#include "datamodeler/model/entity.hpp"

Entity::Entity(std::string name) : ModelComponent(name)
{
}

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

// вернуть атрибут по имени
Attribute& Entity::attribute(std::string name) const
{
    return _getElement(m_attributes, name);
}

// получить список имен атрибутов
std::vector<std::string> Entity::attributes() const
{
    std::vector<std::string> names;
    for (auto const& e : m_attributes)
    {
        names.push_back(e->name());
    }
    return names;
}

Entity::~Entity()
{
}
