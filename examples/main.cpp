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

// показать скрипт
void showGeneratedScript(const Model& model)
{
	try {
		qDebug("%s", ScriptGenerator::generateScript(model).toUtf8().constData());
	} catch (std::invalid_argument) {
		std::cout << "Необходимо доработать модель:" << std::endl;
		for (const QString & str : ScriptGenerator::problemsReadyList(model))
		{
			std::cout << str.toStdString() << std::endl;
		}
	}
}

int main(int argc, char **argv)
{
//	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);

	// считать данные о СУБД
	Config::initTypes("./types.json");
	// проверка методов конфига
	configCheck();

	// при создании модели задается СУБД
	Model* model = new Model("PostgreSQL");

	// создается и настраивается сущность
	Entity* e1 = new Entity();
	model->addEntity(e1);

	// создается и настраивается атрибут
	std::string typeDomain = "Character";
	std::string type = "varchar";
	std::string typeTemplate = Config::typeParmetersTemplate(model->dbms(), typeDomain, type);
	Attribute* e1a1 = new Attribute(typeDomain, {type, typeTemplate});
	e1->addAttribute(e1a1, "e1a1");
	e1a1->setPrimaryKey(true);
	e1a1->setParameters("(5)");

	// создается второй атрибут (имя задается по умолчанию)
	typeDomain = "DateTime";
	type = "time";
	typeTemplate = Config::typeParmetersTemplate(model->dbms(), typeDomain, type);
	Attribute* e1a2 = new Attribute(typeDomain, {type, typeTemplate});
	e1->addAttribute(e1a2, "e1a2");
	e1a2->setNullable(true);
	e1a2->setParameters("(6) with time zone");

	Entity* e2 = new Entity();
	model->addEntity(e2);
	Attribute* e2a1 = new Attribute(typeDomain, {type, typeTemplate});
	e2->addAttribute(e2a1, "e2a1");
	e2a1->setPrimaryKey(true);
	e2a1->setParameters("(5)");

	// добавление связей
	model->addRelationship(new Relationship(Relationship::RELATION_TYPE::Identifying,
											{model->entityName(e1), model->entityName(e2)}));
//	model->addRelationship(new Relationship(Relationship::RELATION_TYPE::NonIdentifying,
//											{model->entityName(e1), model->entityName(e1)}));

//	 выводится скрипт по модели
	qDebug() << "" << "------Before---------" << "";
	showGeneratedScript(*model);

//	model->undo();
//	model->undo();
//	model->undo();
//	model->redo();

//	qDebug() << "" << "------After----------" << "";
//	showGeneratedScript(*model);

//	 сохранить в файл
//	model->save("1.txt");

//	 загрузить из файла (репозиторий обнулился)
//	model = Model::load("1.txt");

	return 0;
}
