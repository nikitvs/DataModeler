#pragma once
#include "_modelComponent.hpp"

class Attribute : public ModelComponent
{
private:
    std::string m_typeDomain;
    std::string m_name;
public:
    // enum TYPE_DOMAIN {Numeric, Character, Datetime, Binary};

    Attribute(std::string typeDomain, std::string name);
    ~Attribute();
};

