#pragma once

#include <string>

class Entity;
class Attribute;
class Model;

class ScriptGenerator
{
private:
    const Model* m_model;
    
    std::string _attributeType(const Attribute* const attribute) const;       // возвращает тип данных с дополнительными параметрами типа
    std::string _attributeParameters(const Attribute* const attribute) const; // возвращает дополнительные параметры
    std::string _scriptForEntity(const Entity* const entity) const;

public:
    ScriptGenerator(const Model& model);
    ~ScriptGenerator();
    const Model& model() const;             // вернуть модель
    std::string generateScript() const;     // возвращает sql скрипт для создание БД
};
