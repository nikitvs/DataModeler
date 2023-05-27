#pragma once

#include "datamodeler/model/attribute.hpp"
#include "datamodeler/model/model.hpp"

// тип атрибута
class Entity;
class Attribute;

class ScriptGenerator
{
private:
	// класс табличного атрибута
	class TableAttribute
	{
	private:
		QString name;
		QString tableName;
		QString attributeString;
	public:
		static std::string generateAttributeString(std::string attributeName, const Attribute& attribute);
		TableAttribute(QString name, QString tableName, QString attributeString);
		const QString& getName() const;
		const QString& getTableName() const;
		const QString& getAttributeString() const;
		void setTableName(const QString& newTableName);
	};

	// класс таблицы
	class Table
	{
	public:
		const QString m_name;
		QVector<TableAttribute*> m_mainPrimaryAttributes;
		QVector<TableAttribute*> m_foreignPrimaryAttributes;
		QVector<TableAttribute*> m_simpleAttributes;
		QVector<TableAttribute*> m_simpleForeignAttributes;
		Table(const QString& entityName, const Model& model);
		void setAllForeignAttributes(const QVector<Table*>& tables, const Model& model);
		~Table();
	};

	// класс табличного оператора
	class TableOperator
	{
	protected:
		QString openingParenthesis = "(";
		QString closingParenthesis = ")";
		QString endingSymbol = ";";
		QString endLine = "\n";
		QString headerForTableScript(QString tableName) const;
		virtual QString operatorName() const = 0;
		virtual QString getTableOperatorBody(const Table& table) const;
	public:
		const QString& getEndLine() const;
		QString generateOperatorScript(const Table& table) const;
	};

	// класс оператора создания таблицы
	class CreateTableOperator : public TableOperator
	{
	private:
		QString operatorName() const override;
		QString getTableOperatorBody(const Table& table) const override;
	};

	// класс оператора изменения таблицы
	class AlterTableOperators : public TableOperator
	{
	private:
		enum class KEY_TYPE {PRIMARY, FOREIGN};
		QString addKey(const KEY_TYPE& keyType, const QVector<QString>& attributes, const QString& tableName = "") const;
		QString operatorName() const override;
	public:
		QString generatePrimaryKeysScripts(const Table& table) const;
		QString generateForeignKeysScripts(const Table& table) const;
	};

private:
	static QString _attributeType(const Attribute* const attribute);		// возвращает тип данных с дополнительными параметрами типа
	static QString _attributeParameters(const Attribute* const attribute);	// возвращает дополнительные параметры
	static QString _scriptForAttribute(const QString& attributeName,
									   const Attribute* const attribute);
	static QString _scriptForEntity(const QString& name,
									const Model& model);					// возвращает скрипт для сущности
	static Table* _getTableForEntity(const Entity& entity);

public:
	static QList<QString> problemsReadyList(const Model& model);		// возвращает список проблем генерации
	static QString generateScript(const Model& model);					// возвращает sql скрипт для создание БД
};
