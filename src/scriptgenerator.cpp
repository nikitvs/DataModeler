#include "datamodeler/scriptgenerator.hpp"

#include <QTextStream>

QList<QString> ScriptGenerator::problemsReadyList(const Model& model)
{
	QList<QString> problemsList;
	for (const auto & entityName : model.entities())
	{
		Entity* entity = model.entity(entityName);
		for (const auto & attributeName : entity->attributes())
		{
			Attribute* attribute = entity->attribute(attributeName);
			if (attribute->type().empty())
			{
				problemsList.push_back(QString("Не задан тип данных для атрибута %1 сущности %2.").
									   arg(QString::fromStdString(attributeName),
										   QString::fromStdString(entityName)));
			}
		}
	}
	for (const auto & relationName : model.relationships())
	{
		Relationship* relationship = model.relationship(relationName);
		if (relationship->type() == Relationship::RELATION_TYPE::ManyToMany)
		{
			problemsList.push_back(QString("Не разрешено отношение manyToMany для сущностей %1 и %2.").
								   arg(QString::fromStdString(relationship->entitiesPair().first),
									   QString::fromStdString(relationship->entitiesPair().second)));
		}
	}
	return problemsList;
}

//**************************************
//********Дополнительные классы*********
//**************************************

//********Table*********
ScriptGenerator::Table::Table(const QString& entityName, const Model& model)
	: m_name(entityName)
{
	const Entity* entity = model.entity(entityName.toStdString());
	// добавить исходные атрибуты в соответсвующие списки
	for (auto const & attributeName : entity->attributes())
	{
		const Attribute* curAttributeName = entity->attribute(attributeName);
		TableAttribute* newTA = new TableAttribute
				(
					QString::fromStdString(attributeName), entityName,
					QString::fromStdString(TableAttribute::generateAttributeString(attributeName,
																				   *curAttributeName))
				);
		if (curAttributeName->primaryKey()) {
			// в список первичных ключей
			m_mainPrimaryAttributes.push_back(newTA);
		} else {
			// в список обычных
			m_simpleAttributes.push_back(newTA);
		}
	}
	// добавить атрибуты из связей в соответсвующие списки
	for (auto const & relationName : model.relationships())
	{
		const Relationship* curRelationship = model.relationship(relationName);
		// если целевая сущность - наша сущность
		if (curRelationship->to() == entityName.toStdString())
		{
			// исходная сущность
			std::string fromEntityName = curRelationship->from();
			const Entity* fromEntity = model.entity(fromEntityName);
			// по всем атрибутам
			for (auto const & curAttributeName : fromEntity->attributes())
			{
				const Attribute* curAttribute = fromEntity->attribute(curAttributeName);
				// только для первичных
				if (!curAttribute->primaryKey()) continue;
				if (curRelationship->type() == Relationship::RELATION_TYPE::Identifying) {
					if (curRelationship->isLoop()) continue;
					// список первичных внешних
					m_foreignPrimaryAttributes.push_back(new TableAttribute
														 (
															 QString::fromStdString(curAttributeName), fromEntityName.c_str(),
															 QString::fromStdString(TableAttribute::generateAttributeString(curAttributeName,
																															*curAttribute))
														 ));
				} else if (curRelationship->type() == Relationship::RELATION_TYPE::NonIdentifying) {
					// список обычных внешних
					m_simpleForeignAttributes.push_back(new TableAttribute
														(
															QString::fromStdString(curAttributeName), fromEntityName.c_str(),
															QString::fromStdString(TableAttribute::generateAttributeString(curAttributeName,
																														   *curAttribute))
														));
				}
			}
		}
	}

}

ScriptGenerator::Table::~Table()
{
	for (auto i = m_foreignPrimaryAttributes.begin(); i != m_foreignPrimaryAttributes.end(); ++i)
		delete *i;
	for (auto i = m_mainPrimaryAttributes.begin(); i != m_mainPrimaryAttributes.end(); ++i)
		delete *i;
	for (auto i = m_simpleAttributes.begin(); i != m_simpleAttributes.end(); ++i)
		delete *i;
	for (auto i = m_mainPrimaryAttributes.begin(); i != m_mainPrimaryAttributes.end(); ++i)
		delete *i;
}

//********TableAttribute*********
ScriptGenerator::TableAttribute::TableAttribute(QString name,
												QString tableName,
												QString attributeString)
	: name(name)
	, tableName(tableName)
	, attributeString(attributeString)
{
}

const QString& ScriptGenerator::TableAttribute::getName() const
{
	return name;
}

const QString& ScriptGenerator::TableAttribute::getTableName() const
{
	return tableName;
}

const QString& ScriptGenerator::TableAttribute::getAttributeString() const
{
	return attributeString;
}

std::string ScriptGenerator::TableAttribute::generateAttributeString(std::string attributeName,
																	 const Attribute& attribute)
{
	return  attributeName + " " +
			attribute.type().c_str() +
			attribute.parameters().c_str() + " " +
			(attribute.nullable() ? "NULL" : "NOT NULL");
}

//********TableOperator*********
const QString& ScriptGenerator::TableOperator::getEndLine() const
{
	return endLine;
}

QString ScriptGenerator::TableOperator::headerForTableScript(QString tableName) const
{
	return operatorName() + QString(" TABLE %1").arg(tableName);
}

QString ScriptGenerator::TableOperator::getTableOperatorBody(const Table& table) const
{
	return QString(headerForTableScript(table.m_name) + getEndLine());
}

QString ScriptGenerator::TableOperator::generateOperatorScript(const Table& table) const
{
	return getTableOperatorBody(table) + endingSymbol + endLine + endLine;
}

//********CreateTableOperator*********
QString ScriptGenerator::CreateTableOperator::operatorName() const
{
	return "CREATE";
}

QString ScriptGenerator::CreateTableOperator::getTableOperatorBody(const Table& table) const
{
	QString script;
	script += TableOperator::getTableOperatorBody(table) + openingParenthesis + getEndLine();

	for (auto const & curTableAttribute : table.m_mainPrimaryAttributes)
	{
		script += "    " + curTableAttribute->getAttributeString() + "," + endLine;
	}
	for (auto const & curTableAttribute : table.m_foreignPrimaryAttributes)
	{
		script += "    " + curTableAttribute->getAttributeString() + "," + endLine;
	}
	for (auto const & curTableAttribute : table.m_simpleAttributes)
	{
		script += "    " + curTableAttribute->getAttributeString() + "," + endLine;
	}
	for (auto const & curTableAttribute : table.m_simpleForeignAttributes)
	{
		script += "    " + curTableAttribute->getAttributeString() + "," + endLine;
	}
	// убрать последнюю запятую
	script = script.left(script.size() - QString("," + endLine).size()) + endLine;
	script += closingParenthesis;

	return script;
}

//********AlterTableOperators*********
QString ScriptGenerator::AlterTableOperators::addKey(const KEY_TYPE& keyType,
													 const QVector<QString>& attributes,
													 const QString& tableName) const
{
	QString attributesStr = openingParenthesis;
	for (auto const & curAttribute : attributes)
	{
		attributesStr += curAttribute + ",";
	}
	attributesStr = attributesStr.left(attributesStr.size() - QString(",").size()) + closingParenthesis;

	QString script;
	script += "    ADD " + QString((keyType == KEY_TYPE::PRIMARY ? "PRIMARY" : "FOREIGN")) + " KEY " + attributesStr;
	if (keyType == KEY_TYPE::FOREIGN)
	{
		script += " REFERENCES " + tableName + attributesStr;
	}
	return script;
}

QString ScriptGenerator::AlterTableOperators::operatorName() const
{
	return "ALTER";
}

QString ScriptGenerator::AlterTableOperators::generateAlterScripts(const Table& table) const
{
	QString scripts;

	if (!table.m_mainPrimaryAttributes.empty() || !table.m_foreignPrimaryAttributes.empty())
	{
		QVector<QString> primaryAttributes;
		for (auto const & curAttribute : table.m_mainPrimaryAttributes)
		{
			primaryAttributes += curAttribute->getName();
		}
		for (auto const & curAttribute : table.m_foreignPrimaryAttributes)
		{
			primaryAttributes += curAttribute->getName();
		}
		scripts += headerForTableScript(table.m_name) + getEndLine() +
				   addKey(KEY_TYPE::PRIMARY, primaryAttributes) + endingSymbol + endLine + endLine;
	}

	if (!table.m_foreignPrimaryAttributes.empty() || !table.m_simpleForeignAttributes.empty())
	{
		QMap<QString, QVector<QString>> foreignAttributes;
		for (auto const & attribute : table.m_foreignPrimaryAttributes)
		{
			if (!foreignAttributes.contains(attribute->getTableName()))
				foreignAttributes.insert(attribute->getTableName(), {});
			foreignAttributes.find(attribute->getTableName())->push_back(attribute->getName());
		}
		for (auto const & attribute : table.m_simpleForeignAttributes)
		{
			if (!foreignAttributes.contains(attribute->getTableName()))
				foreignAttributes.insert(attribute->getTableName(), {});
			foreignAttributes.find(attribute->getTableName())->push_back(attribute->getName());
		}

		for (auto iter = foreignAttributes.begin(); iter != foreignAttributes.end(); ++iter)
		{
			QVector<QString> attributes;
			for (auto nameIter = iter.value().begin(); nameIter != iter.value().end(); ++nameIter)
			{
				attributes += *nameIter;
			}

			scripts += headerForTableScript(table.m_name) + getEndLine() +
					   addKey(KEY_TYPE::FOREIGN, attributes, iter.key()) + endingSymbol + endLine + endLine;
		}
	}
	return scripts;
}

//********************************************************
//********Генерирует sql скрипт для создания БД***********
//********************************************************
QString ScriptGenerator::generateScript(const Model& model)
{
	if (!problemsReadyList(model).empty())
	{
		throw std::invalid_argument("Модель не готова к формированию скрипта.");
	}

	// составить таблицы
	QVector<Table*> tables;
	for (auto const & curEntityName : model.entities())
	{
		tables.push_back(new Table(QString::fromStdString(curEntityName), model));
	}

	QString script;
	// создать таблицы
	for (auto const & curTable : tables)
	{
		CreateTableOperator create;
		script += create.generateOperatorScript(*curTable);
	}
	// добавить первичные и внешние ключи
	for (auto const & curTable : tables)
	{
		AlterTableOperators alter;
		script += alter.generateAlterScripts(*curTable);
	}

	// удалить таблицы
	for (auto i = tables.begin(); i != tables.end(); ++i) delete *i;

	return script;

}
