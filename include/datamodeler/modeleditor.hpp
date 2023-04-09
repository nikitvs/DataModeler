//#pragma once
//#include "model/model.hpp"
//#include "model/entity.hpp"
//#include "model/relationship.hpp"
//#include "model/attribute.hpp"


//class ModelSaver;

//// класс модели БД
//class ModelEditor : public QObject
//{
//	Q_OBJECT
//protected:
//    bool _existObject(const std::vector<std::string>& namesVector, const std::string name);
//    std::string _generateObjectName(const std::vector<std::string>& namesVector, const std::string name, const std::string baseName);
//    void _throwElementNotExist(const std::vector<std::string>& namesVector, const std::string name);
//    void _throwElementExist(const std::vector<std::string>& namesVector, const std::string name);

    
//    // вернуть объект по имени
//    // template <typename T>
//    // T* ModelEditor::_getElement(const std::list<T*>& elementsList, const std::string elemName) const
//    // {
//    //     return *std::find_if(elementsList.begin(), elementsList.end(), [elemName](T* e){return e->name() == elemName;});
//    // }
//    // Entity* _entity(std::string name) const;
//    // Relationship* _relationship(std::string name) const;

//private slots:
//	void _saveModel();

//private:
//    Model& m_model;
//	ModelSaver* m_modelsaver;
//	int m_currentStep;

//public:
//	ModelEditor(Model& model, QObject* parent = nullptr);

//    std::vector<std::string> availableDBMS();
//    std::vector<std::string> availableDomains(std::string DBMS);
//    std::vector<std::string> availableTypes(std::string DBMS, std::string domain);

//    std::string modelDbms() const;
//    std::vector<std::string> entities() const;
//    std::vector<std::string> relationships() const;

//	void addEntity(std::string name);
//	void deleteEntity(std::string name);
//    void addRelationship(Relationship::RELATION_TYPE type,
//                         std::string entity_1,
//                         std::string entity_2,
//                         std::string name = "");
//    void deleteRelationship(std::string name);
//	void addAttrubute(std::string entityName, std::string typeDomain, std::string type, std::string name = "");
//    void deleteAttrubute(std::string entityName, std::string attributeName);
//	bool redo();
//	bool undo();
//    ~ModelEditor();
//};
