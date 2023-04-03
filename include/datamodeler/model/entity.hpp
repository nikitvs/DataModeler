#pragma once

#include <vector>
#include <string>

// #include "attribute.hpp"
// #include "_modelComponent.hpp"
#include "../src/model/_modelComponent.hpp"

class Attribute;

// класс сущности
class Entity : public ModelComponent
{
private:
    // std::string m_name;     // имя сущности
    std::list<Attribute*> m_attributes;
public:
    Entity(std::string name);
    // std::string name() const;
    void addAttribute(Attribute* attribute);
    // void deleteAttribute(Attribute* attribute);
    void deleteAttribute(std::string name);
    Attribute* attribute(std::string name) const;
    std::vector<std::string> attributes() const;
    // const std::list<Attribute*>& attributes() const;
    // int addAttribute(std::string typeDomain, std::string name = "");
    // void addAttribute(Attribute);
    ~Entity();
};
