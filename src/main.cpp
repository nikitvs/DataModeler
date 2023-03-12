#include <iostream>
// #include "modelComponents/attribute.hpp"
#include "modelComponents/relationship.hpp"
#include "modelComponents/entity.hpp"
#include "config.hpp"
#include "model.hpp"

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
    Entity* e1 = new Entity;
    Entity* e2 = new Entity;
    model.addEntity(e1);
    model.addEntity(e2);

    // добавить отношение
    Relationship* r1 = new Relationship(Relationship::RELATION_TYPE::Identifying, e1, e2);
    model.addRelationship(r1);

    // 2 - 1
    std::cout << model.entities().size() << std::endl << model.relationships().size() << std::endl;

    // 1 - 0
    model.delEntity(e1);
    std::cout << model.entities().size() << std::endl << model.relationships().size() << std::endl;

    return 0;
}