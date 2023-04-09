#pragma once
#include <vector>
// #include "_modelComponent.hpp"
#include "../src/model/_modelComponent.hpp"

class Attribute : public ModelComponent
{
	Q_OBJECT
private:
    // std::string m_name;     // имя объекта
    std::string m_typeDomain;
    std::string m_type;
    std::string m_parametersTemplate;   // возможно временное поле
    std::string m_parameters;
    bool m_primaryKey = false; // первичный ключ
    bool m_nullable   = true; // NULL
    // std::vector<int>* const m_sizeParameters; // параметры размера
    // std::vector<std::string>* const m_textParameters; // текстовые параметры
public:
    // enum TYPE_DOMAIN {Numeric, Character, Datetime, Binary};

	Attribute(std::string typeDomain,
			  std::string type = "",
			  std::string parametersTemplate = "",
			  std::string name = "",
			  QObject* parent = nullptr);
    // std::string name() const;
	QJsonObject toJson() const override;
	static Attribute* fromJson(const QJsonObject& jsonObj, QObject* parent = nullptr);
	void setTypeDomain(std::string typeDomain, std::string type, std::string parametersTemplate);                 // тип данных
	std::string typeDomain() const;
    void setType(std::string type, std::string parametersTemplate);                 // тип данных
    std::string type() const;
    std::string parametersTemplate() const;         // шаблон параметров
    void setParameters(std::string parameters);     // параметры
    std::string parameters() const;
    void setPrimaryKey(bool);                       // первичный ключ
    bool primaryKey() const;
    bool setNullable(bool);                         // NULL
    bool nullable() const;
    // void setTypeDomain(std::string type);
    // std::string typeDomain() const;
    // std::vector<int>& sizeParameters() const;
    // std::vector<std::string>& textParameters() const;
    ~Attribute();
};

