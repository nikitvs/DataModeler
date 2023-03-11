#include <string>

class Attribute
{
private:
    std::string m_dataType;
public:
    enum TYPE_DOMAIN {Numeric, Character, Datetime, Binary};

    Attribute();
    Attribute(Attribute::TYPE_DOMAIN);
    ~Attribute();
};

