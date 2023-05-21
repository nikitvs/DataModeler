#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"
#include <QJsonArray>

Entity::Entity(QObject* parent) : ModelComponent(parent)
{
}

QJsonObject Entity::toJson() const
{
	QJsonObject jsonObj = ModelComponent::toJson();
	jsonObj.insert("attributes", ModelComponent::toJson(m_attributes));
	return jsonObj;
}

Entity* Entity::fromJson(const QJsonObject& jsonObj, QObject* parent)
{
	Entity* entity = new Entity(parent);
	ModelComponent::fromJson<Entity>(jsonObj, entity);
	QJsonArray attributesArr = jsonObj.value("attributes").toArray();
	for (QJsonArray::iterator it = attributesArr.begin(); it != attributesArr.end(); ++it)
	{
		entity->addAttribute(Attribute::fromJson((*it).toObject(), entity), Attribute::nameFromJson((*it).toObject()));
	}
	return entity;
}

void Entity::addAttribute(Attribute* attribute, std::string name)
{
	if (name.empty()) name = _generateObjectName("A_", m_attributes);
	ModelComponent::_addElement(name, attribute, m_attributes);
	QObject::connect(attribute, &Attribute::_changed, this, &Entity::_changed);
}

void Entity::deleteAttribute(std::string name)
{
	return ModelComponent::_deleteElement(name, m_attributes);
}

void Entity::renameAttribute(std::string oldName, std::string newName)
{
	return ModelComponent::_renameElement(oldName, newName, m_attributes);
}

// вернуть атрибут по имени
Attribute* Entity::attribute(std::string name) const
{
	return ModelComponent::_getElement(name, m_attributes);
}

std::string Entity::attributeName(const Attribute* attribute) const
{
	return ModelComponent::_getElement(attribute, m_attributes);
}

// получить список имен атрибутов
std::vector<std::string> Entity::attributes() const
{
	return ModelComponent::_getNamesVector(m_attributes);
}

Entity::~Entity()
{
	ModelComponent::_clearMap(m_attributes);
}
