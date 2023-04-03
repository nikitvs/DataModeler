#include "datamodeler/scriptgenerator.hpp"

#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/model.hpp"

ScriptGenerator::ScriptGenerator(const Model& model)
    : m_model(&model)
{
}

// возвращает тип данных с дополнительными параметрами
std::string ScriptGenerator::_attributeType(const Attribute* const attribute) const
{
    return attribute->type() + attribute->parameters();
}

// возвращает дополнительные параметры
std::string ScriptGenerator::_attributeParameters(const Attribute* const attribute) const
{
    std::string parameters;
    if (attribute->primaryKey()){
        parameters += "PRIMARY KEY";
    } else {
        if (attribute->nullable()){
            parameters += "NULL";
        } else {
            parameters += "NOT NULL";
        };
    }
    return parameters;
}

std::string ScriptGenerator::_scriptForEntity(const Entity* const entity) const
{
    std::string endCommand       = ";\n";
    std::string endStr           = ",\n";
    std::string tab              = "    ";
    std::string openingParenthesis  = "\n(\n";
    std::string closingParenthesis = ")";

    std::stringstream script;
    script << "CREATE TABLE " << entity->name();
    // если атрибуты есть
    if (entity->attributes().size() > 0)
    {
        script << openingParenthesis;
        for (const auto & curAttributeName : entity->attributes()) {
            const Attribute* curAttribute = entity->attribute(curAttributeName);
            script << tab << curAttributeName            << " " \
                    << _attributeType(curAttribute)       << " " \
                    << _attributeParameters(curAttribute) << (curAttributeName != entity->attributes().back() ? endStr : "\n");
        }
        script << closingParenthesis;
    }
    script << endCommand;
}

// вернуть модель
const Model& ScriptGenerator::model() const
{
    return *m_model;
}

// возвращает sql скрипт для создание БД
std::string ScriptGenerator::generateScript() const
{
// создать скрипт из компонентов
    std::stringstream script;
    for (const auto & curEntityName : model().entities())
    {
        script << _scriptForEntity(m_model->entity(curEntityName));
        script << "\n";
    }

    return script.str();
}

ScriptGenerator::~ScriptGenerator()
{
}
