#include <list>

// объявление класса сущности
class Entity;
// объявление класса отношения
class Relationship;

class Model
{
public:
    enum DATABASE_TYPE {mySQL};                     // поддерживаемые СУБД
    
private:
    Model::DATABASE_TYPE m_databaseType;            // СУБД
    std::list<Entity*> m_entitiesList;              // список сущностей
    std::list<Relationship*> m_relationshipsList;   // список отношений между сущностями

public:
    Model(Model::DATABASE_TYPE);
    // Model::DATABASE_TYPE getDatabaseType();
    // void addEntity(const Entity*);
    ~Model();
};