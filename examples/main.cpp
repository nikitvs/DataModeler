#include <iostream>
#include "datamodeler/config.hpp"
#include "datamodeler/model/model.hpp"
#include "datamodeler/model/entity.hpp"
#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/relationship.hpp"
#include "datamodeler/scriptgenerator.hpp"

#include <QTextCodec>

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
	std::cout << "Шаблон для PostgreSQL - DateTime - time: " <<
				 Config::typeParmetersTemplate("PostgreSQL", "DateTime", "time") <<
				 std::endl << std::endl<< std::endl;
}

int main()
{
//	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);

    // считать данные о СУБД
    Config::initTypes("./types.json");
    // проверка методов конфига
	configCheck();

	// при создании модели задается СУБД
	Model model(Config::availableDBMS().at(1));

	// создается и настраивается сущность
	model.addEntity(new Entity(), "E1");
	Entity* e1 = model.entity("E1");
	e1->setAdditionalModelParameters(QString("(x,y)"));

	// создается и настраивается атрибут
	std::string typeDomain = Config::availableDomains(model.dbms()).at(0);
	e1->addAttribute(new Attribute(typeDomain, Config::availableTypes(model.dbms(), typeDomain).at(0)), "E1A1");
	Attribute* e1a1 = e1->attribute("E1A1");
	e1a1->setPrimaryKey(true);
	e1a1->setParameters("(4) parameter");

	// создается второй атрибут (имя задается по умолчанию)
	e1->addAttribute(new Attribute(typeDomain, Config::availableTypes(model.dbms(), typeDomain).at(1)));

	// создается отношение (имя задается по умолчанию)
	model.addEntity(new Entity());

//	model.addRelationship(new Relationship(Relationship::RELATION_TYPE::NonIdentifying, {"E1", "E1"}), "R2");

	// выводится скрипт по модели (!!! потом добавится исключение, когда модель не готова !!!)
	qDebug("%s", QString::fromStdString(ScriptGenerator::generateScript(model)).toUtf8().constData());

	model.undo();
	model.undo();
	model.undo();
	model.redo();

	qDebug() << "---------------";
	qDebug("%s", QString::fromStdString(ScriptGenerator::generateScript(model)).toUtf8().constData());


    return 0;
}
