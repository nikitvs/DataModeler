#include <algorithm>
#include <stdexcept>

#include "model.hpp"
#include "entity.hpp"
#include "relationship.hpp"

// проверка, что в списке уже есть объект с таким именем
template <class T>
void Model::_checkName(const std::list<T*>& list, const std::string name) const
{
    if (std::find_if(list.begin(), list.end(), [name](T* e){return e->name() == name;}) != list.end())
    {
        throw std::invalid_argument("There is already an element with this name!");
    }
}

// сгенерировать имя для объекта
template <class T>
std::string Model::_genBaseName(const std::list<T*>& list, const std::string baseName) const
{
    int index = list.size() + 1;
    // если уже есть элемент с таким именем, инкрементировать индекс
    while (std::find_if(list.begin(), list.end(), [=](T* e)
        {
            return (baseName + std::to_string(index) == e->name());
        }) != list.end())
    {
        ++index;
    }
    return baseName + std::to_string(index);
}

// вернуть объект по имени
template <class T>
T& Model::_getElement(const std::list<T*>& list, const std::string name) const
{
    return *(*std::find_if(list.begin(), list.end(), [name](T* e){return e->name() == name;}));
}

Model::Model()
{
}

// методы добавления сущности в модель
Entity& Model::addEntity(std::string name)
{
    // порождать исключение, когда сущность с таким именем уже есть
    _checkName(m_entitiesList, name);
    

    Entity* entity = new Entity(name);
    m_entitiesList.push_back(entity);
    return *entity;
}
// дополнительный метод, как способ для параметра указать зависимое от поля класса значение по умолчанию
Entity& Model::addEntity()
{
    return addEntity(_genBaseName(m_entitiesList, "E_"));
}

// вернуть сущность по имени
Entity& Model::entity(std::string name)
{
    return _getElement(m_entitiesList, name);
}

// удалить сущность из модели (+ связанные отношения)
void Model::removeEntity(std::string name)
{
    // убрать сущность из списка
    Entity* l_entity = &entity(name);
    m_entitiesList.remove(l_entity);

    std::list<Relationship*> tmpDelRelationList; // список отношений, которые будут удалены
    // опредедлить отношения для удаления
    for(auto iter = m_relationshipsList.begin(); iter!=m_relationshipsList.end(); ++iter)
    {
        const Relationship* const currentRelationship = static_cast<Relationship*>(*iter);
        if (currentRelationship->entitiesPair().first == name || currentRelationship->entitiesPair().second == name)
            tmpDelRelationList.push_back(*iter);
    }
    // удаление отношений, связанных с сущностью
    for(auto iter = tmpDelRelationList.begin(); iter!=tmpDelRelationList.end(); ++iter)
    {
        removeRelationship(*iter);
    }
    // удалить сущность
    delete l_entity;
}

// добавить отношение в модель
Relationship& Model::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2, std::string name)
{
    // порождать исключение, когда отношение с таким именем уже есть
    _checkName(m_relationshipsList, name);

    Relationship* relationship = new Relationship(type, &entity(entity_1), &entity(entity_1), name);
    m_relationshipsList.push_back(relationship);
    return *relationship;
}
// аналогичная уловка как для сущностей
Relationship& Model::addRelationship(Relationship::RELATION_TYPE type, std::string entity_1, std::string entity_2)
{
    return addRelationship(type, entity_1, entity_2, _genBaseName(m_relationshipsList, "R_"));
}

// вернуть отношение по имени
Relationship& Model::relationship(std::string name)
{
    return _getElement(m_relationshipsList, name);
}

// удалить отношение из модели
void Model::removeRelationship(Relationship* relationship)
{
    m_relationshipsList.remove(relationship);
    delete relationship;
}
void Model::removeRelationship(std::string name)
{
    removeRelationship(&_getElement(m_relationshipsList, name));
}

// получить список имен сущностей
std::vector<std::string> Model::entities()
{
    std::vector<std::string> names;
    for (auto const& e : m_entitiesList)
    {
        names.push_back(e->name());
    }
    return names;
}
// получить список имен отношений
std::vector<std::string> Model::relationships()
{
    std::vector<std::string> names;
    for (auto const& r : m_relationshipsList)
    {
        names.push_back(r->name());
    }
    return names;
}

// // получить список сущностей
// std::list<Entity*> Model::entities()
// {
//     return m_entitiesList;
// }
// // получить список отношений
// std::list<Relationship*> Model::relationships()
// {
//     return m_relationshipsList;
// }

// осфободить память для всех сущностей и отношений
Model::~Model()
{
    for(auto iter = m_entitiesList.begin(); iter!=m_entitiesList.end(); ++iter)
    {
        delete *iter;
    }
    for(auto iter = m_relationshipsList.begin(); iter!=m_relationshipsList.end(); ++iter)
    {
        delete *iter;
    }
}