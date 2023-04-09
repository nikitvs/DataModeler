#pragma once
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

class ModelComponent : public QObject
{
	Q_OBJECT
private:
    std::string m_name;     // имя объекта
	QVariant m_additionalModelParameters;

signals:
	void _changed();

public:
	ModelComponent(std::string name, QObject* parent = nullptr)
		: QObject(parent)
		, m_name(name)
	{};
    ~ModelComponent(){};

	std::string name() const
	{
		return m_name;
	}
	void setName(std::string name)
	{
		m_name = name;
	}

	QVariant additionalModelParameters() const
	{
		return m_additionalModelParameters;
	}
	void setmAdditionalModelParameters(QVariant parameters)
	{
		m_additionalModelParameters = parameters;
	}

protected:
    // добавить рабочее ограничение : только наследники ModelComponent
    // ---- здесь и далее template используется с указателем и без
	// ---- указатель нужен для разрешения неопределенности при перегрузках функции (здесь ради примера)

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	T* _getElement(const std::list<T*>& elementsList, const std::string elemName) const
	{
		auto pointer = *std::find_if(elementsList.begin(), elementsList.end(), [elemName](T* e){return e->name() == elemName;});
		if (pointer == *elementsList.end())
		{
			pointer = nullptr;
		}
		return pointer;
	}

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    std::vector<std::string> _getNamesList(const std::list<T*>& elementsList) const
    {
        std::vector<std::string> names;
        for (auto const& curElement : elementsList)
        {
            names.push_back(curElement->name());
        }
        return names;
    }

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    void _addElement(T* element, std::list<T*>& elementsList)
    {
		elementsList.push_back(element);
    }

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    void _deleteElement(T* element, std::list<T*>& elementsList)
    {
        elementsList.remove(element);
        delete element;
    }

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    void _clearList(std::list<T*>& elementsList)
    {
        for(auto element : elementsList)
        {
            delete element;
        }
        elementsList.clear();
    }

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	QJsonArray toJson(const std::list<T*>& elementsList) const
	{
		QJsonArray jsonArr;
		for (const std::string & elementName : _getNamesList(elementsList))
		{
			jsonArr.append(_getElement(elementsList, elementName)->toJson());
		}
		return jsonArr;
	}

	virtual QJsonObject toJson() const
	{
		QJsonObject jsonObj;
		jsonObj.insert("name", QString::fromStdString(name()));
		jsonObj.insert("additionalModelParameters", additionalModelParameters().toString());
		return jsonObj;
	}

//	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
//	void fromJson(const QJsonArray& jsonArr, std::list<T*>& elementsList)
//	{
//		for (auto const & jsonValue : jsonArr)
//		{
//			_addElement(T::fromJson(jsonValue.toObject()), elementsList);
//		}
//	}

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	static void fromJson(const QJsonObject& jsonObj, T* modelComponent)
	{
		modelComponent->setName(jsonObj.value("name").toString().toStdString());
		modelComponent->setmAdditionalModelParameters(jsonObj.value("additionalModelParameters").toVariant());
	}

};
