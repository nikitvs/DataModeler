#include <string>

class Attribute
{
private:
    std::string m_dataType;
public:
    enum class Domain {Number, String, Datetime, Blob};

    Attribute(/* args */);
    ~Attribute();
};

