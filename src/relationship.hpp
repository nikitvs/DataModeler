#include <list>

// объявление класса сущности
class Entity;

// класс отношений между сущностями
class Relationship
{
public:
    enum RELATION_TYPE {Identifying, NonIdentifying, ManyToMany};   // типы отношений 
private:
    Relationship::RELATION_TYPE type;                               // тип отношения
    std::pair<const Entity, const Entity> m_entitiesPair;           // объекты отношения
public:
    Relationship(Relationship::RELATION_TYPE);
    ~Relationship();
};
