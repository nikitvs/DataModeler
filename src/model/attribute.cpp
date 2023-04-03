#include "datamodeler/model/attribute.hpp"

Attribute::Attribute(std::string typeDomain, std::string name, std::string type, std::string parametersTemplate)
    : m_typeDomain(typeDomain)
    // , m_name(name)
    , m_type(type)
    , m_parametersTemplate(parametersTemplate)
    , ModelComponent(name)
{
}

// std::string Attribute::name() const
// {
//     return m_name;
// }

// доступ к типу данных
void Attribute::setType(std::string type, std::string parametersTemplate)
{
    m_type = type;
    m_parametersTemplate = parametersTemplate;
    m_parameters = "";
}
std::string Attribute::type() const {return m_type;}

// доступ к шаблону параметров
std::string Attribute::parametersTemplate() const {return m_parametersTemplate;}

// доступ к параметрам
void Attribute::setParameters(std::string parameters) {m_parameters = parameters;}
std::string Attribute::parameters() const {return m_parameters;}

// задает флаг первичный ключ
void Attribute::setPrimaryKey(bool primaryKey)
{
    if (primaryKey)
        m_nullable = false;
    m_primaryKey = primaryKey;
}
bool Attribute::primaryKey() const {return m_primaryKey;}

// задает флаг допустимости null
bool Attribute::setNullable(bool nullable)
{
    // если стоит первичный ключ - этот флаг менять нельзя
    if (m_primaryKey)
        return false;

    m_nullable = nullable;
    return true;
}

bool Attribute::nullable() const {return m_nullable;}

Attribute::~Attribute()
{
}