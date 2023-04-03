#pragma once
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>

class ModelComponent
{
private:
    std::string m_name;     // имя объекта

public:
    ModelComponent(std::string name) : m_name(name){};
    ~ModelComponent(){};
    std::string name() const {return m_name;}

protected:
    // добавить рабочее ограничение : только наследники ModelComponent
    // ---- здесь и далее template используется с указателем и без
    // ---- указатель нужен для разрешения неопределенности при перегрузках функции (здесь ради примера)

    // // проверить, что такое имя уже есть
    // template <typename T, typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>* = nullptr>
    // void _checkName(const std::list<T*>& list, const std::string name) const
    // {
    //     if (std::find_if(list.begin(), list.end(), [name](T* e){return e->name() == name;}) != list.end())
    //     {
    //         std::stringstream ss;
    //         ss << "There is already an element with name: " << "\"" << name << "\"" << "!";
    //         throw std::invalid_argument(ss.str());
    //     }
    // };

    // // выдать исключение если уже есть объект с таким именем
    // void _checkName(const std::list<std::string>& nameslist, const std::string name) const
    // {
    //     if (std::find_if(nameslist.begin(), nameslist.end(), [name](std::string currentName)
    //     {
    //         return currentName == name;
    //     }) != nameslist.end())
    //     {
    //         std::stringstream ss;
    //         ss << "There is already an element with name: " << "\"" << name << "\"" << "!";
    //         throw std::invalid_argument(ss.str());
    //     }
    // };


    // // сгенерировать имя для объекта
    // template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    // std::string _genBaseName(const std::list<T*>& list, const std::string baseName) const
    // {
    //     int index = list.size() + 1;
    //     // если уже есть элемент с таким именем, инкрементировать индекс
    //     while (std::find_if(list.begin(), list.end(), [=](T* e)
    //         {
    //             return (baseName + std::to_string(index) == e->name());
    //         }) != list.end())
    //     {
    //         ++index;
    //     }
    //     return baseName + std::to_string(index);
    // }

    // вернуть объект по имени
    // template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    // template <typename T>
    // T* _getElement(const std::list<T*>& elementsList, const std::string elemName) const
    // {
    //     const auto res = std::find_if(elementsList.begin(), elementsList.end(), [elemName](T* e){return e->name() == elemName;});
    //     if (res == elementsList.end())
    //     {
    //         std::stringstream ss;
    //         ss << "There is no element with name: " << "\"" << elemName << "\"" << "!";
    //         throw std::invalid_argument(ss.str());
    //     }
    //     return *res;
    // }

    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    T* _getElement(const std::list<T*>& elementsList, const std::string elemName) const
    {
        return *std::find_if(elementsList.begin(), elementsList.end(), [elemName](T* e){return e->name() == elemName;});
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

};
