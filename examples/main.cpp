#include <iostream>
// #include "model/attribute.hpp"
#include "datamodeler/model/relationship.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/model.hpp"
#include "datamodeler/config.hpp"
#include "datamodeler/scriptgenerator.hpp"
#include "datamodeler/modeleditor.hpp"
// для вывода в консоль кириллицы
#include <windows.h>

void configCheck()
{
        // получить список СУБД
    std::vector<std::string> listDBMS = Config::availableDBMS();
    std::cout << "Доступные СУБД:" << std::endl;
    for (auto iter = listDBMS.begin(); iter != listDBMS.end(); ++iter)
    {
        std::cout << " - " << *iter << std::endl;
    }
    std::cout << std::endl;

    // получить список доменов
    std::cout << "Доступные домены PostgreSQL:" << std::endl;
    std::vector<std::string> listDomains = Config::availableDomains("PostgreSQL");
    for (auto iter = listDomains.begin(); iter != listDomains.end(); ++iter)
    {
        std::cout << " - " << *iter << std::endl;
    }
    std::cout << std::endl;

    // получить список типов данных
    std::cout << "Доступные типы данных PostgreSQL - Character:" << std::endl;
    std::vector<std::string> listTypes = Config::availableTypes("PostgreSQL", "Character");
    for (auto iter = listTypes.begin(); iter != listTypes.end(); ++iter)
    {
        std::cout << " - " << *iter << std::endl;
    }
    std::cout << std::endl;

    // получить шаблон параметров типов данных
    std::cout << "Шаблон для PostgreSQL - DateTime - time: " << Config::typeParmetersTemplate("PostgreSQL", "DateTime", "time") << std::endl;
}

int main()
{
    // для вывода в консоль кириллицы
    SetConsoleOutputCP(CP_UTF8);

    // считать данные о СУБД
    Config::initTypes("./types.json");
    // проверка методов конфига
    configCheck();

    std::string DBMS = "PostgreSQL";
    Model model(DBMS, "Model_1");

    ModelEditor editor(model);

    editor.addEntity("Entity_1");
    editor.addAttrubute("Entity_1", "Character", "varchar");

    // a1.setPrimaryKey(true);
    // std::string type1 = Config::availableTypes(DBMS, domain).at(0);
    // a1.setType(type1,  Config::typeParmetersTemplate(DBMS, domain, type1));


    // Attribute& a2 = e1.addAttribute(domain);
    // a2.setNullable(false);
    // std::string type2 = Config::availableTypes(DBMS, domain).at(1);
    // a2.setType(type2,  Config::typeParmetersTemplate(DBMS, domain, type2));
    // a2.setParameters("");

    // Entity& e2 = model.addEntity("E_with_attrs2");
    // std::string domain2 = Config::availableDomains(DBMS).back();
    // std::cout << domain2 << std::endl;
    // Attribute& a3 = e2.addAttribute(domain2);
    // a3.setPrimaryKey(true);
    // std::string type3 = Config::availableTypes(DBMS, domain).at(1);
    // a3.setType(type3, Config::typeParmetersTemplate(DBMS, domain, type3));

    ScriptGenerator sGenerator(model);
    std::cout << sGenerator.generateScript() << std::endl;

    return 0;
}
