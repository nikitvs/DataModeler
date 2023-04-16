#include <QJsonDocument>
#include <QSqlQuery>
#include <QSqlError>
#include "modelsaver.hpp"

void ModelSaver::_createDatabaseContent(const QSqlDatabase& database) const
{
	database.exec(QString("CREATE TABLE %1(id INTEGER, %2 TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT));").
				  arg(m_table, m_column));
}

void ModelSaver::_dropDatabaseContent(const QSqlDatabase& database) const
{
	database.exec(QString("drop table %1").arg(m_table));
}

ModelSaver::ModelSaver()
    : m_table("model")
    , m_column("jsonmodel")
    , m_sequence("model_id_seq")
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("./modelDatabase.db");

//  проверка подключения
    if (!m_db.open()) {
		qDebug() << "Ошибка подключения к базе данных" << m_db.lastError().text();
        return;
    }

	ModelSaver::_createDatabaseContent(m_db);
}

void ModelSaver::saveJson(const QJsonObject& json, int step)
{
	QSqlDatabase db = QSqlDatabase::database();
	db.exec(QString("delete from %1 where id > '%2'").arg(m_table, QString::number(step)));
	db.exec(QString("UPDATE SQLITE_SEQUENCE SET seq = %1 WHERE name = '%2'").arg(QString::number(step), m_table));
	db.exec(QString("insert into %1(%2) values('%3')").arg(m_table, m_column, QJsonDocument(json).toJson(QJsonDocument::Compact)));
}

QJsonObject ModelSaver::loadJson(int step)
{
    QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query = db.exec(QString("select %1 from %2 where id='%3'").arg(m_column, m_table, QString::number(step)));
	query.next();
	return QJsonDocument::fromJson(query.value(0).toByteArray()).object();
}

int ModelSaver::maxStep()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(QString("select count(*) from %2").arg(m_table));
    query.next();
    return query.value(0).toInt();
}

ModelSaver::~ModelSaver()
{
	QSqlDatabase db = QSqlDatabase::database();
	ModelSaver::_dropDatabaseContent(db);
	if(db.isOpen())
        db.close();
}
