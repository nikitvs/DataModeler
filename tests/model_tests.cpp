#include <gtest/gtest.h>
#include "datamodeler/model/model.hpp"

#include <iostream>

// именование сущностей в модели
TEST(ModelTests, EntitesNames) {
    Model m("mySql");
    
    m.addEntity();
    m.addEntity("SpecialEntity");
    m.addEntity();
    
    EXPECT_STREQ("E_1",           m.entities().at(0).c_str());
    EXPECT_STREQ("SpecialEntity", m.entities().at(1).c_str());
    EXPECT_STREQ("E_3",           m.entities().at(2).c_str());

    m.removeEntity("SpecialEntity");
    m.addEntity();
    // E_4, а не E_3, т.к. такая уже есть
    EXPECT_STREQ("E_4", m.entities().back().c_str());
}

// именование отношений в модели
TEST(ModelTests, RelationsNames) {
    Model m("mySql");
    m.addEntity("123");
    m.addRelationship(Relationship::RELATION_TYPE::ManyToMany, "123", "123");
    EXPECT_STREQ("R_1", m.relationships().back().c_str());
    m.addRelationship(Relationship::RELATION_TYPE::ManyToMany, "123", "123", "R_3");
    m.addRelationship(Relationship::RELATION_TYPE::ManyToMany, "123", "123");
    EXPECT_STREQ("R_4", m.relationships().back().c_str());
}

// удаление объектов из модели
TEST(ModelTests, RemoveEntitiesAndRelations) {
    Model m("mySql");
    // удаление сущностей
    m.addEntity("e1");
    m.addEntity("e2");
    m.addEntity("e3");
    m.removeEntity("e1");
    EXPECT_STREQ("e2", m.entities().at(0).c_str());
    EXPECT_STREQ("e3", m.entities().at(1).c_str());
    // удаление отношений
    m.addRelationship(Relationship::RELATION_TYPE::NonIdentifying, "e3", "e2", "Rrem");
    m.addRelationship(Relationship::RELATION_TYPE::NonIdentifying, "e3", "e2", "Rtest");
    m.addRelationship(Relationship::RELATION_TYPE::NonIdentifying, "e3", "e2", "Rtest2");
    m.removeRelationship("Rtest");
    EXPECT_STREQ("Rrem", m.relationships().at(0).c_str());
    EXPECT_STREQ("e3", m.relationship(m.relationships().at(0)).entitiesPair().first.c_str());
    EXPECT_STREQ("Rtest2", m.relationships().at(1).c_str());
    EXPECT_STREQ("e2", m.relationship(m.relationships().at(1)).entitiesPair().second.c_str());
}
