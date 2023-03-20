#include <gtest/gtest.h>
#include "model/model.hpp"

// именование сущностей в модели
TEST(ModelTests, ModelsNames) {
    Model m;
    
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
