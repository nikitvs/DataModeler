#pragma once
#include <list>
#include <sstream>
#include <algorithm>
#include <type_traits>

class ModelComponent
{
private:
    std::string m_name;     // имя объекта
public:
    ModelComponent(std::string name) : m_name(name){};

    std::string name() const
    {
        return m_name;
    }

    // добавить рабочее ограничение : только наследники ModelComponent
    // ---- здесь и далее template используется с указателем и без
    // ---- указатель нужен для разрешения неопределенности при перегрузках функции (здесь ради примера)

    // проверить, что такое имя уже есть
    template <typename T, typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>* = nullptr>
    void _checkName(const std::list<T*>& list, const std::string name) const
    {
        if (std::find_if(list.begin(), list.end(), [name](T* e){return e->name() == name;}) != list.end())
        {
            std::stringstream ss;
            ss << "There is already an element with name: " << "\"" << name << "\"" << "!";
            throw std::invalid_argument(ss.str());
        }
    };

    // сгенерировать имя для объекта
    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    std::string _genBaseName(const std::list<T*>& list, const std::string baseName) const
    {
        int index = list.size() + 1;
        // если уже есть элемент с таким именем, инкрементировать индекс
        while (std::find_if(list.begin(), list.end(), [=](T* e)
            {
                return (baseName + std::to_string(index) == e->name());
            }) != list.end())
        {
            ++index;
        }
        return baseName + std::to_string(index);
    }

    // вернуть объект по имени
    template <typename T, typename = typename std::enable_if_t<std::is_base_of<ModelComponent, T>::value, T>>
    T& _getElement(const std::list<T*>& list, const std::string name) const
    {
        const auto res = std::find_if(list.begin(), list.end(), [name](T* e){return e->name() == name;});
        if (res == list.end())
        {
            std::stringstream ss;
            ss << "There is no element with name: " << "\"" << name << "\"" << "!";
            throw std::invalid_argument(ss.str());
        }
        return *(*res);
    }

    ~ModelComponent(){};
};
