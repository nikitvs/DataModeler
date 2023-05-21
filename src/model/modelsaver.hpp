#pragma once
#include <QJsonObject>
#include <QSqlDatabase>

class Model;

class ModelSaver
{
	QSqlDatabase m_db;
	QString m_table;
	QString m_column;
	QString m_sequence;

private:
	void _createDatabaseContent(const QSqlDatabase& database) const;
	void _dropDatabaseContent(const QSqlDatabase& database) const;

public:
	ModelSaver();
	void close();
	void saveJson(const QJsonObject& model, int step);
	QJsonObject loadJson(int step);
	int maxStep();
	~ModelSaver();
};
