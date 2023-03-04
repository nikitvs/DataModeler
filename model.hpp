#include "entity.hpp"
#include <list>

class Model
{
public:
    enum class databaseType {mySQL}; 
    
private:
    Model::databaseType m_databaseType;
    std::list<Entity> m_entityList;

public:
    Model(Model::databaseType);
    Model::databaseType getDatabaseType();
    void addEntity(const Entity&);
    ~Model();
};