#include <iostream>
// #include "model/attribute.hpp"
#include "datamodeler/model/relationship.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/model.hpp"
#include "datamodeler/config.hpp"
#include "datamodeler/scriptgenerator.hpp"

int main() 
{
    Config::initTypes("./types.json");

//    // получить список СУБД
//    std::vector<std::string> listDBMS = Config::availableDBMS();
//    for(auto iter = listDBMS.begin(); iter!=listDBMS.end(); ++iter)
//    {
//        std::cout << *iter << std::endl;
//    }

//    // получить список доменов
//    std::vector<std::string> listDomains = Config::availableDomains("mySQL");
//    for(auto iter = listDomains.begin(); iter!=listDomains.end(); ++iter)
//    {
//        std::cout << *iter << std::endl;
//    }

//    // получить список типов данных
//    std::vector<std::string> listTypes = Config::availableTypes("PostgreSQL", "Character");
//    for(auto iter = listTypes.begin(); iter!=listTypes.end(); ++iter)
//    {
//        std::cout << *iter << std::endl;
//    }

//    // получить флаг динамичного размера
//    std::cout << Config::dynamicType("PostgreSQL", "Character", "varchar") << std::endl;
//    std::cout << Config::dynamicType("mySQL", "Numeric", "integer") << std::endl;

    std::string DBMS = "PostgreSQL";
    Model model(DBMS);
    std::cout << DBMS << std::endl;

    Entity& e1 = model.addEntity("E_with_attrs");
    std::string domain = Config::availableDomains(DBMS).front();
    std::cout << domain << std::endl;
    Attribute& a1 = e1.addAttribute(domain);
    Attribute& a2 = e1.addAttribute(domain);
    a1.setPrimaryKey(true);
    a2.setNullable(false);
    a1.setType(Config::availableTypes(DBMS, domain).at(0));
    a2.setType(Config::availableTypes(DBMS, domain).at(1));
    a2.setLength(12);

    Entity& e2 = model.addEntity("E_with_attrs1");
    std::string domain2 = Config::availableDomains(DBMS).back();
    std::cout << domain2 << std::endl;
    Attribute& a3 = e2.addAttribute(domain);
    Attribute& a4 = e2.addAttribute(domain);
    a3.setPrimaryKey(true);
    a4.setNullable(false);
    a3.setType(Config::availableTypes(DBMS, domain).at(0));
    a4.setType(Config::availableTypes(DBMS, domain).at(1));
    a4.setLength(12);


    ScriptGenerator sGenerator(model);
    std::cout << sGenerator.generateScript() << std::endl;


    return 0;
}


