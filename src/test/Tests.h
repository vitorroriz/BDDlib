
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

using namespace ClassProject;
//DEFINE YOUR TESTS HERE

TEST (FalseTest, FalseID) {
    Manager *manager = new Manager();
    ASSERT_EQ (0, manager->False());
}

TEST (TrueTest, TrueID) {
    Manager *manager = new Manager();
    ASSERT_EQ (1, manager->True());
}

TEST (uniqueTableSizeTest, uniqueTableSize) {
    Manager *manager = new Manager();
    ASSERT_EQ (2, manager->uniqueTableSize());
}

TEST (createVarTest, uniqueTableSize) {
    Manager *manager = new Manager();
    manager->createVar("a");
    ASSERT_EQ (3, manager->uniqueTableSize());
}

TEST (createVarTest, varAttributes) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    BDD_Node* var = manager->getBDDNode(id);
    ASSERT_EQ ("a", var->label);
    ASSERT_EQ (id, var->top_var);
    ASSERT_EQ (manager->True(), var->high);
    ASSERT_EQ (manager->False(), var->low);
    ASSERT_EQ (id, var->id);
}

TEST (isConstantTest, LeafNode) {
    Manager *manager = new Manager();
    ASSERT_EQ (true, manager->isConstant(manager->True()));
    ASSERT_EQ (true, manager->isConstant(manager->False()));
}

TEST (isConstantTest, NonLeafNode) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (false, manager->isConstant(id));
}

TEST (isVariableTest, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (true, manager->isVariable(id));
}

TEST (isVariableTest, LeafNode) {
    Manager *manager = new Manager();
    ASSERT_EQ (false, manager->isVariable(manager->True()));
    ASSERT_EQ (false, manager->isVariable(manager->False()));
}

#endif 
