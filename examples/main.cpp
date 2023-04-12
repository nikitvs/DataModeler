#include <iostream>
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/model.hpp"
#include "datamodeler/model/relationship.hpp"
#include "datamodeler/model/modelsaver.hpp"
#include "datamodeler/config.hpp"
#include "datamodeler/scriptgenerator.hpp"
//#include "datamodeler/modeleditor.hpp"

#include <QTextCodec>

// для вывода в консоль кириллицы
// #include <windows.h>

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
    // SetConsoleOutputCP(CP_UTF8);

    // считать данные о СУБД
    Config::initTypes("./types.json");
    // проверка методов конфига
//    configCheck();

	std::string DBMS = "PostgreSQL";
	Model model(DBMS, "Model_1");
	ScriptGenerator sg(model);

    model.addEntity(new Entity("E1"));
    model.addEntity(new Entity("E2"));
    model.entity("E1")->addAttribute(new Attribute("td", "E1A1"));
	model.entity("E1")->attribute("E1A1")->setPrimaryKey(true);
	model.entity("E1")->attribute("E1A1")->setParameters("(4) parameter");
	model.entity("E1")->addAttribute(new Attribute("td", "E1A2"));
	model.entity("E1")->attribute("E1A2")->setPrimaryKey(false);
	model.entity("E1")->attribute("E1A2")->setNullable(false);
	model.entity("E1")->attribute("E1A2")->setParameters("(7, 5)");
	model.entity("E2")->addAttribute(new Attribute("td", "E2A1"));
	model.addEntity(new Entity("E3"));
//    model.addRelationship(new Relationship(Relationship::RELATION_TYPE::NonIdentifying, "E1", "E1", "R1"));
    model.addRelationship(new Relationship(Relationship::RELATION_TYPE::Identifying, "E1", "E2", "R2"));

    qDebug("%s", QString::fromStdString(sg.generateScript()).toUtf8().constData());

    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();
    qDebug() << model.undo();

    qDebug() << "";
    qDebug() << model.undo();
    qDebug() << "";

    qDebug() << model.redo();
    qDebug() << model.redo();

    qDebug() << "---------------";
    qDebug("%s", QString::fromStdString(sg.generateScript()).toUtf8().constData());


//	ModelSaver ms;
//	ms.saveJson(QJsonArray::fromStringList(QStringList("123")), 0);
//	ms.saveJson(QJsonArray::fromStringList(QStringList("123")), 1);
//	ms.saveJson(QJsonArray::fromStringList(QStringList("234")), 2);
//	qDebug() << ms.maxStep();
//	ms.loadModel(2);



    return 0;
}
