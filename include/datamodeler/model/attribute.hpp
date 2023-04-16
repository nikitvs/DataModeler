#pragma once
#include "_modelComponent.hpp"

// класс атрибута
class Attribute : public ModelComponent
{
	Q_OBJECT
private:
	std::string m_typeDomain;			// домен типа данных
	std::string m_type;					// тип данных
	std::string m_parametersTemplate;	// шаблон параметров типа данных
	std::string m_parameters;			// параметры типа данных
	bool m_primaryKey = false;			// первичный ключ
	bool m_nullable   = true;			// NULL

public:
	Attribute(std::string typeDomain,
			  std::pair<std::string, std::string> typeAndParametersTemplate = {"", ""},
			  QObject* parent = nullptr);						// конструктор (домент типа обязателен)
	void setTypeDomain(std::string typeDomain,
					   std::pair<std::string, std::string>
					   typeAndParametersTemplate = {"", ""});	// задать домен типа данных
	std::string typeDomain() const;								// получить домен типа данных
	void setType(std::string type,
				 std::string parametersTemplate);				// задать тип данных
	std::string type() const;									// получить тип данных
	std::string parametersTemplate() const;						// получить шаблон параметров
	void setParameters(std::string parameters);					// задать параметры типа данных
	std::string parameters() const;								// получить параметры типа данных
	void setPrimaryKey(bool);									// задать первичный ключ
	bool primaryKey() const;									// получить первичный ключ
	bool setNullable(bool);										// задать значене для NULL
	bool nullable() const;										// получить значене для NULL
	QJsonObject toJson() const override;						// превратить объект атрибута в json объект
	static Attribute* fromJson(const QJsonObject& jsonObj,		// создать объект атрибута из json объекта
							   QObject* parent = nullptr);
    ~Attribute();
};

