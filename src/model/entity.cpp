#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"

Entity::Entity(std::string name) : ModelComponent(name)
{
}

void Entity::addAttribute(Attribute* attribute)
{
    ModelComponent::_addElement(attribute, m_attributes);
}

void Entity::deleteAttribute(std::string name)
{
    ModelComponent::_deleteElement(attribute(name), m_attributes);
}

// вернуть атрибут по имени
Attribute* Entity::attribute(std::string name) const
{
    return ModelComponent::_getElement(m_attributes, name);
}

// получить список имен атрибутов
std::vector<std::string> Entity::attributes() const
{
    return ModelComponent::_getNamesList(m_attributes);
}

Entity::~Entity()
{
}
