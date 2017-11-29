
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

using namespace ClassProject;
//DEFINE YOUR TESTS HERE

TEST (FalseTest, FalseID) {
    Manager *manager = new Manager();
    ASSERT_EQ (manager->False(), BDD_ID(0));
}

TEST (TrueTest, TrueID) {
    Manager *manager = new Manager();
    ASSERT_EQ (manager->True(), BDD_ID(1));
}

TEST (uniqueTableSizeTest, uniqueTableSize) {
    Manager *manager = new Manager();
    ASSERT_EQ (manager->uniqueTableSize(), 2);
}

#endif 
