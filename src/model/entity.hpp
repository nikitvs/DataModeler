#pragma once

#include <vector>
#include <string>

#include "attribute.hpp"
#include "_modelComponent.hpp"

// класс сущности
class Entity : public ModelComponent
{
private:
    std::string m_name;     // имя сущности
    std::list<Attribute*> m_attributes;
public:
    Entity(std::string);
//    std::string name() const;
    Attribute& addAttribute(std::string typeDomain, std::string name = "");
    // int addAttribute(std::string typeDomain, std::string name = "");
    // void addAttribute(Attribute);
    ~Entity();
};
