#include "datamodeler/model/attribute.hpp"
//#include "attribute.hpp"

Attribute::Attribute(std::string typeDomain,
					 std::pair<std::string, std::string> typeAndParametersTemplate,
					 QObject* parent)
    : m_typeDomain(typeDomain)
	, m_type(typeAndParametersTemplate.first)
	, m_parametersTemplate(typeAndParametersTemplate.second)
	, ModelComponent(parent)
{
}

QJsonObject Attribute::toJson() const
{
	QJsonObject jsonObj = ModelComponent::toJson();
	jsonObj.insert("typeDomain", QString::fromStdString(typeDomain()));
	jsonObj.insert("type", QString::fromStdString(type()));
	jsonObj.insert("parametersTemplate", QString::fromStdString(parametersTemplate()));
	jsonObj.insert("parameters", QString::fromStdString(parameters()));
	jsonObj.insert("primaryKey", QString::fromStdString(_fromBoolToString(primaryKey())));
	jsonObj.insert("nullable", QString::fromStdString(_fromBoolToString(nullable())));
	return jsonObj;
}

Attribute* Attribute::fromJson(const QJsonObject& jsonObj, QObject* parent)
{
	Attribute* attribute = new Attribute(jsonObj.value("typeDomain").toString().toStdString(),
										 std::pair<std::string, std::string> (
											jsonObj.value("type").toString().toStdString(),
											jsonObj.value("parametersTemplate").toString().toStdString()),
										 parent);
	ModelComponent::fromJson<Attribute>(jsonObj, attribute);
	attribute->setParameters(jsonObj.value("parameters").toString().toStdString());
	attribute->setPrimaryKey(_fromStringToBool(jsonObj.value("primaryKey").toString().toStdString()));
	attribute->setNullable(_fromStringToBool(jsonObj.value("nullable").toString().toStdString()));
	return attribute;
}


void Attribute::setTypeDomain(std::string typeDomain, std::pair<std::string, std::string> typeAndParametersTemplate)
{
	m_typeDomain = typeDomain;
	setType(typeAndParametersTemplate.first, typeAndParametersTemplate.second);
}
std::string Attribute::typeDomain() const
{
	return m_typeDomain;
}

// доступ к типу данных
void Attribute::setType(std::string type, std::string parametersTemplate)
{
    m_type = type;
    m_parametersTemplate = parametersTemplate;
    m_parameters = "";

	emit _changed();
}
std::string Attribute::type() const
{
	return m_type;
}

// доступ к шаблону параметров
std::string Attribute::parametersTemplate() const
{
	return m_parametersTemplate;
}

// доступ к параметрам
void Attribute::setParameters(std::string parameters)
{
	if (!QRegExp(QString::fromStdString(parametersTemplate())).
				 exactMatch(QString::fromStdString(parameters)))
	{
		throw std::invalid_argument(QString("Параметры типа данных не соответствуют шаблону").toStdString());
	}

	m_parameters = parameters;
	emit _changed();
}
std::string Attribute::parameters() const
{
	return m_parameters;
}

// задает флаг первичный ключ
void Attribute::setPrimaryKey(bool primaryKey)
{
    if (primaryKey)
        m_nullable = false;
    m_primaryKey = primaryKey;

	emit _changed();
}
bool Attribute::primaryKey() const
{
	return m_primaryKey;
}

// задает флаг допустимости null
bool Attribute::setNullable(bool nullable)
{
    // если стоит первичный ключ - этот флаг менять нельзя
    if (m_primaryKey)
        return false;

    m_nullable = nullable;
	emit _changed();
    return true;
}

bool Attribute::nullable() const
{
	return m_nullable;
}

Attribute::~Attribute()
{
}
