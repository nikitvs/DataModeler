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
    model.addEntity("E_1");
    model.addEntity("E_2");
//    model.entity("123");

    model.addRelationship(Relationship::RELATION_TYPE::Identifying, "E_1", "E_2", "R_E1_E2");
//    model.addRelationship(Relationship::RELATION_TYPE::Identifying, "E_1", "E_2", "R_E1_E2");

    Entity& e = model.addEntity("E_with_attrs");
    e.addAttribute(c.availableDomains("mySQL").front());

    return 0;
}
