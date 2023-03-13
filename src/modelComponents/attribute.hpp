#pragma once

#include <string>

class Attribute
{
private:
    std::string m_dataType;
public:
    // enum TYPE_DOMAIN {Numeric, Character, Datetime, Binary};

    Attribute();
    Attribute(std::string, std::string);
    ~Attribute();
};

