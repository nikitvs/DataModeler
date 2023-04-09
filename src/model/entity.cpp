#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"
#include <QJsonArray>
//#include "entity.hpp"
//#include "attribute.hpp"

Entity::Entity(std::string name, QObject* parent) : ModelComponent(name, parent)
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
	Entity* entity = new Entity(jsonObj.value("name").toString().toStdString());
	ModelComponent::fromJson<Entity>(jsonObj, entity);
	for (auto const & jsonValue : jsonObj.value("attributes").toArray())
	{
		entity->addAttribute(Attribute::fromJson(jsonValue.toObject(), entity));
	}
	return entity;
}

void Entity::addAttribute(Attribute* attribute)
{
    ModelComponent::_addElement(attribute, m_attributes);

	QObject::connect(attribute, &Attribute::_changed, this, &Entity::_changed);
	emit _changed();
}

void Entity::deleteAttribute(std::string name)
{
    ModelComponent::_deleteElement(attribute(name), m_attributes);

	emit _changed();
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
