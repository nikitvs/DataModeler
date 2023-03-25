#include "datamodeler/scriptgenerator.hpp"
#include "datamodeler/config.hpp"

std::string ScriptGenerator::_attributeType(const Attribute& attribute) const
{
    std::string resType = attribute.type();
    if (Config::isDynamicType(model().dbms(), attribute.typeDomain(), attribute.type()))
        resType += "(" + std::to_string(attribute.length()) + ")";
    return resType;
}

std::string ScriptGenerator::_attributeParameters(const Attribute& attribute) const
{
    std::string parameters;
    if (attribute.nullable()){
        parameters += "NULL";
    } else {
        parameters += "NOT NULL";
    };
    if (attribute.primaryKey()) parameters += " PRIMARY KEY";
    return parameters;
}

ScriptGenerator::ScriptGenerator(const Model& model)
    : m_model(&model)
{
}

const Model& ScriptGenerator::model() const
{
    return *m_model;
}

std::string ScriptGenerator::generateScript() const
{
    std::string endCommand       = ";\n";
    std::string endStr           = ",\n";
    std::string tab              = "    ";
    std::string openParenthesis  = "\n(\n";
    std::string closeParenthesis = ")";

// создать скрипт из компонентов
    std::stringstream script;
    for (const auto & curEntityName : model().entities()) {
        script << "CREATE TABLE " << curEntityName;
        Entity& curEntity = model().entity(curEntityName);
        if (curEntity.attributes().size() > 0)
        {
            script << openParenthesis;
            for (const auto & curAttributeName : curEntity.attributes()) {
                Attribute curAttribute = curEntity.attribute(curAttributeName);
                script << tab << curAttributeName            << " " \
                       << _attributeType(curAttribute)       << " " \
                       << _attributeParameters(curAttribute) << (curAttributeName != curEntity.attributes().back() ? endStr : "\n");
            }
            script << closeParenthesis;
        }
        script << endCommand;
    }

    return script.str();
}

ScriptGenerator::~ScriptGenerator()
{
}
