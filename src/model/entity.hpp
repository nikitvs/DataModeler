#pragma once

#include <list>
#include <string>

// класс сущности
class Entity
{
private:
    std::string m_name;     // имя сущности
public:
    Entity();
    Entity(std::string);
    std::string name() const;
    // void addAttribute(Attribute);
    ~Entity();
};