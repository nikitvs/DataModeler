#include "datamodeler/model/relationship.hpp"

std::string Relationship::_enumToString(RELATION_TYPE type)
{
	switch (type) {
	case Relationship::RELATION_TYPE::Identifying:
		return "Identifying";
		break;
	case Relationship::RELATION_TYPE::NonIdentifying:
		return "NonIdentifying";
		break;
	case Relationship::RELATION_TYPE::ManyToMany:
		return "ManyToMany";
		break;
	default:
		throw std::invalid_argument("Нет такого типа отношения!");
		break;
	}
}

Relationship::RELATION_TYPE Relationship::_stringToEnum(std::string type)
{
	if (type == "Identifying") {
		return Relationship::RELATION_TYPE::Identifying;
	} else if (type == "NonIdentifying") {
		return Relationship::RELATION_TYPE::NonIdentifying;
	} else if (type == "ManyToMany") {
		return Relationship::RELATION_TYPE::ManyToMany;
	} else {
		throw std::invalid_argument("Нет такого типа отношения!");
	}
}

Relationship::Relationship(Relationship::RELATION_TYPE type,
						   std::pair<std::string, std::string> entitiesPair,
						   QObject* parent)
	: m_type(type)
	, m_entitiesPair(entitiesPair)
	, ModelComponent(parent)
{}

const std::pair<std::string, std::string>& Relationship::entitiesPair() const
{
	return m_entitiesPair;
}

bool Relationship::isLoop() const
{
	return (m_entitiesPair.first == m_entitiesPair.second);
}

bool Relationship::hasEntity(std::string entityName) const
{
	return (from() == entityName) || (to() == entityName);
}

std::string Relationship::from() const
{
	return m_entitiesPair.first;
}

std::string Relationship::to() const
{
	return m_entitiesPair.second;
}

Relationship::RELATION_TYPE Relationship::type() const
{
	return m_type;
}

bool Relationship::setType(RELATION_TYPE type)
{
	m_type = type;
	return true;
}

QJsonObject Relationship::toJson() const
{
	QJsonObject jsonObj = ModelComponent::toJson();
	jsonObj.insert("type", QString::fromStdString(_enumToString(type())));
	QJsonArray entities;
	entities.append(QString::fromStdString(entitiesPair().first));
	entities.append(QString::fromStdString(entitiesPair().second));
	jsonObj.insert("entitiesPair", entities);
	return jsonObj;
}

Relationship* Relationship::fromJson(const QJsonObject& jsonObj, QObject* parent)
{
	Relationship* relationship = new Relationship(_stringToEnum(jsonObj.value("type").toString().toStdString()),
												  std::pair<std::string, std::string>(
												  jsonObj.value("entitiesPair").toArray().at(0).toString().toStdString(),
												  jsonObj.value("entitiesPair").toArray().at(1).toString().toStdString()));
	ModelComponent::fromJson<Relationship>(jsonObj, relationship);
	return relationship;
}
