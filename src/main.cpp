#include <iostream>
// #include "model/attribute.hpp"
#include "model/relationship.hpp"
#include "model/entity.hpp"
#include "model/model.hpp"
#include "config.hpp"

int main() 
{
//    Config c;
// // получить список СУБД
//     std::vector<std::string> listDBMS = c.availableDBMS();
//     for(auto iter = listDBMS.begin(); iter!=listDBMS.end(); ++iter)
//     {
//         std::cout << *iter << std::endl;
//     }

// // получить список доменов
//     std::vector<std::string> listDomains = c.availableDomains("mySQL");
//     for(auto iter = listDomains.begin(); iter!=listDomains.end(); ++iter)
//     {
//         std::cout << *iter << std::endl;
//     }

// // получить список типов данных
//     std::vector<std::string> listTypes = c.availableTypes("PostgreSQL", "Character");
//     for(auto iter = listTypes.begin(); iter!=listTypes.end(); ++iter)
//     {
//         std::cout << *iter << std::endl;
//     }

// // получить флаг динамичного размера
//     std::cout << c.dynamicType("PostgreSQL", "Character", "varchar") << std::endl;
//     std::cout << c.dynamicType("mySQL", "Numeric", "integer") << std::endl;


    Config c;
    Model model;
    // добавить сущности
    Entity e1 = model.addEntity("Entity_1");
    Entity e2 = model.addEntity("Entity_2");

    // добавить отношение
    model.addRelationship(Relationship::RELATION_TYPE::Identifying, e1.name(), e2.name());
    model.addRelationship(Relationship::RELATION_TYPE::Identifying, e2.name(), e2.name());

    // 2 - 1
    std::cout << "Entities: " << model.entities().size() <<  ", relations: " << model.relationships().size() << std::endl;

    // 1 - 0
    model.removeEntity("Entity_1");
    std::cout << "Entities: " << model.entities().size() <<  ", relations: " << model.relationships().size() << std::endl;

    std::cout << "Second entity name: " << model.entity("Entity_2").name() << std::endl << \
                "Model first entity name: " << model.entities().front() << std::endl << \
                "Model first relationship name: " << model.relationships().front() << std::endl << \
                "Firs relationship entities names pair: " << model.relationship(model.relationships().front()).entitiesPair().first << " " \
                                                          << model.relationship(model.relationships().front()).entitiesPair().second \
                << std::endl;

    return 0;
}