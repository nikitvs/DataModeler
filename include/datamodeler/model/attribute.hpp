#pragma once
#include "_modelComponent.hpp"

class Attribute : public ModelComponent
{
private:
    std::string m_typeDomain;
    std::string m_name;
    std::string m_type;
    bool m_primaryKey = false;
    bool m_nullable   = true;
    int m_length;
public:
    // enum TYPE_DOMAIN {Numeric, Character, Datetime, Binary};

    Attribute(std::string typeDomain, std::string name = "");
    bool setNullable(bool);
    bool nullable() const;
    void setPrimaryKey(bool);
    bool primaryKey() const;
    void setType(std::string type);
    std::string type() const;
    void setTypeDomain(std::string type);
    std::string typeDomain() const;
    void setLength(int length);
    int length() const;
    ~Attribute();
};

