
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

using namespace ClassProject;
//DEFINE YOUR TESTS HERE

TEST (FalseTest, FalseID) {
    Manager *manager = new Manager();
    ASSERT_EQ (BDD_ID(0), manager->False());
}

TEST (TrueTest, TrueID) {
    Manager *manager = new Manager();
    ASSERT_EQ (BDD_ID(1), manager->True());
}

TEST (uniqueTableSizeTest, uniqueTableSize) {
    Manager *manager = new Manager();
    ASSERT_EQ (2, manager->uniqueTableSize());
}

TEST (createVarTest, uniqueTableSize) {
    Manager *manager = new Manager();
    //manager->createVar("a");
    ASSERT_EQ (3, manager->uniqueTableSize());
}

TEST (createVarTest, varAttributes) {
    Manager *manager = new Manager();
   // manager->createVar("a");
    ASSERT_EQ (new BDD_Node("a", 2, manager->True(), manager->False(), 2), manager->getBDDNode(2));
}

#endif 
