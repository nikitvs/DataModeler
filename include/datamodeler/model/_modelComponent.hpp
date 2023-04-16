#pragma once
#include <map>
#include <vector>
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
	QVariant m_additionalModelParameters;

signals:
	void _changed();

private:
	template <typename T, typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>* = nullptr>
	int _getIndex(const std::string& elemName, const std::vector<std::pair<std::string, T*>>& pairsVector) const
	{
		auto it = std::find_if(pairsVector.begin(), pairsVector.end(),
							   [=](auto elem)
		{
			return elem.first == elemName;
		});
		if (it == pairsVector.end()) {
			return -1;
		} else {
			return std::distance(pairsVector.begin(), it);
		}
	}

public:
	ModelComponent(QObject* parent = nullptr) : QObject(parent)
	{};
	~ModelComponent(){};

	const QVariant& additionalModelParameters() const
	{
		return m_additionalModelParameters;
	}
	void setAdditionalModelParameters(const QVariant& parameters)
	{
		m_additionalModelParameters = parameters;
		emit _changed();
	}

//	virtual bool isReady() const = 0;

protected:
    // добавить рабочее ограничение : только наследники ModelComponent
    // ---- здесь и далее template используется с указателем и без
	// ---- указатель нужен для разрешения неопределенности при перегрузках функции (здесь ради примера)

	template <typename T, typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>* = nullptr>
	T* _getElement(const std::string& elemName, const std::vector<std::pair<std::string, T*>>& pairsVector) const
	{
		int index = _getIndex(elemName, pairsVector);
		if (index == -1)
		{
			return nullptr;
		} else {
			return pairsVector.at(index).second;
		}
	}

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	std::vector<std::string> _getNamesVector(const std::vector<std::pair<std::string, T*>>& pairsVector) const
	{
		std::vector<std::string> names;
		for (auto const& curElement : pairsVector)
        {
			names.push_back(curElement.first);
        }
		return names;
	}

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	void _addElement(const std::string& elemName, T* element, std::vector<std::pair<std::string, T*>>& pairsVector)
	{
		if (_getIndex(elemName, pairsVector) == -1) {
			pairsVector.push_back(std::pair<std::string, T*>(elemName, element));
			emit _changed();
		} else {
			throw std::invalid_argument(QString("Warning: Уже есть элемент с именем %1").
										arg(QString::fromStdString(elemName)).toStdString());
		}
	}

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	void _deleteElement(const std::string& elemName, std::vector<std::pair<std::string, T*>>& pairsVector)
    {
		int index = _getIndex(elemName, pairsVector);
		if (index != -1) {
			delete _getElement(elemName, pairsVector);
			pairsVector.erase(pairsVector.begin() + index);
			emit _changed();
		} else {
			throw std::invalid_argument(QString("Warning: Нет элемента с именем %1").
										arg(QString::fromStdString(elemName)).toStdString());
		}
    }

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	void _renameElement(const std::string& oldName, const std::string& newName, std::vector<std::pair<std::string, T*>>& pairsVector)
	{
		int index = _getIndex(oldName, pairsVector);
		if (index != -1 && _getIndex(newName, pairsVector) == -1) {
			(pairsVector.begin() + index)->first = newName;
			emit _changed();
		} else {
			throw std::invalid_argument(QString("Warning: Нет элемента с именем %1 или уже есть элемент с именем %2").
										arg(QString::fromStdString(oldName),
											QString::fromStdString(newName)).toStdString());
		}
	}

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	static void _clearMap(std::vector<std::pair<std::string, T*>>& pairsVector)
    {
		for(auto & element : pairsVector)
        {
			delete element.second;
        }
		pairsVector.clear();
    }

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	QJsonArray toJson(const std::vector<std::pair<std::string, T*>>& pairsVector) const
	{
		QJsonArray jsonArr;
		for (const std::string & elementName : _getNamesVector(pairsVector))
		{
			QJsonObject jsonObj = _getElement(elementName, pairsVector)->toJson();
			jsonObj.insert("name", QString::fromStdString(elementName));
			jsonArr.append(jsonObj);
		}
		return jsonArr;
	}

	virtual QJsonObject toJson() const
	{
		QJsonObject jsonObj;
		jsonObj.insert("additionalModelParameters", additionalModelParameters().toString());
		return jsonObj;
	}

	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	static void fromJson(const QJsonObject& jsonObj, T* modelComponent)
	{
		modelComponent->setAdditionalModelParameters(jsonObj.value("additionalModelParameters").toVariant());
	}

	static std::string nameFromJson(const QJsonObject& jsonObj)
	{
		return jsonObj.value("name").toString().toStdString();
	}

	static std::string _fromBoolToString(const bool par)
	{
		if (par) {
			return "true";
		} else {
			return "false";
		}
	}

	static bool _fromStringToBool(const std::string& par)
	{
		if (par == "true") {
			return true;
		} else {
			return false;
		}
	}

	// сгенерировать имя для объекта
	template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
	std::string _generateObjectName(const std::string& baseName,
									const std::vector<std::pair<std::string, T*>>& pairsVector)
	{
		std::string objectName;
		// если имя пустое - сгенерировать имя
		int index = pairsVector.size() + 1;
		// если уже есть элемент с таким именем, инкрементировать индекс
		while (_getIndex(baseName + std::to_string(index), pairsVector) != -1)
		{
			++index;
		}
		// имя как базовое имя + индекс
		objectName = baseName + std::to_string(index);
		return objectName;
	}
};
