#include <iostream>
#include "modelComponents/attribute.hpp"
#include "config.hpp"

int main() 
{
    Config c;

// получить список СУБД
    // std::vector<std::string> listDBMS = c.availableDBMS();
    // for(auto iter = listDBMS.begin(); iter!=listDBMS.end(); ++iter)
    // {
    //     std::cout << *iter << std::endl;
    // }

// получить список доменов
    // std::vector<std::string> listDomains = c.availableDomains("mySQL");
    // for(auto iter = listDomains.begin(); iter!=listDomains.end(); ++iter)
    // {
    //     std::cout << *iter << std::endl;
    // }

// получить список типов данных
    // std::vector<std::string> listTypes = c.availableTypes("PostgreSQL", "Character");
    // for(auto iter = listTypes.begin(); iter!=listTypes.end(); ++iter)
    // {
    //     std::cout << *iter << std::endl;
    // }

// получить флаг динамичного размера
    std::cout << c.dynamicType("PostgreSQL", "Character", "varchar") << std::endl;
    std::cout << c.dynamicType("mySQL", "Numeric", "integer") << std::endl;

    return 0;
}