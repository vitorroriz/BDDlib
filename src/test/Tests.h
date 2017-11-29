
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

using namespace ClassProject;
//DEFINE YOUR TESTS HERE

TEST (False, FalseNode) {
    Manager *manager = new Manager();
    ASSERT_EQ (manager->False(), BDD_ID(0));
}

#endif 
