#pragma once
#include "model/model.hpp"

class ScriptGenerator
{
private:
    const Model* m_model;

protected:
    std::string _attributeType(const Attribute& attribute) const;
    std::string _attributeParameters(const Attribute& attribute) const;

public:
    ScriptGenerator(const Model& model);
    ~ScriptGenerator();
    const Model& model() const;
    std::string generateScript() const;
};
