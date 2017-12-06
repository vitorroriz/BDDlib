
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

TEST (uniqueTableSizeTest, LeafNodes) {
    Manager *manager = new Manager();
    ASSERT_EQ (2, manager->uniqueTableSize());
}

TEST (uniqueTableSizeTest, Variable) {
    Manager *manager = new Manager();
    manager->createVar("a");
    ASSERT_EQ (3, manager->uniqueTableSize());
}

TEST (uniqueTableSizeTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);
    size_t size1 = manager->uniqueTableSize();
    manager->ite(a,b,c);
    size_t size2 = manager->uniqueTableSize();

    ASSERT_EQ (6, size1);
    ASSERT_EQ (size1,size2);
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

TEST (topVarTest, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (id, manager->topVar(id));
}


TEST (coFactorFalsef, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (manager->False(), manager->coFactorFalse(id));
}

TEST (topVarTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (a, manager->getBDDNode(f)->top_var);
}

TEST (coFactorFalsefx, TerminalCase) {
    Manager *manager = new Manager();
    BDD_ID falseId = manager->False();
    BDD_ID trueId = manager->True();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    ASSERT_EQ (falseId, manager->coFactorFalse(falseId,a));
    ASSERT_EQ (a, manager->coFactorFalse(a,falseId));
    ASSERT_EQ (trueId, manager->coFactorFalse(trueId,a));
    ASSERT_EQ (a, manager->coFactorFalse(a,trueId));
    ASSERT_EQ (falseId, manager->coFactorFalse(a,a));
    ASSERT_EQ (a, manager->coFactorFalse(a,b));
}

TEST (coFactorTruef, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (manager->True(), manager->coFactorTrue(id));
}

TEST (coFactorTruefx, TerminalCase) {
    Manager *manager = new Manager();
    BDD_ID falseId = manager->False();
    BDD_ID trueId = manager->True();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    ASSERT_EQ (falseId, manager->coFactorTrue(falseId,a));
    ASSERT_EQ (a, manager->coFactorTrue(a,falseId));
    ASSERT_EQ (trueId, manager->coFactorTrue(trueId,a));
    ASSERT_EQ (a, manager->coFactorTrue(a,trueId));
    ASSERT_EQ (trueId, manager->coFactorTrue(a,a));
    ASSERT_EQ (a, manager->coFactorTrue(a,b));
}

TEST (iteTest, TerminalCase) {
    Manager *manager = new Manager();
    BDD_ID falseId = manager->False();
    BDD_ID trueId = manager->True();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");

    ASSERT_EQ (falseId, manager->ite(falseId,falseId,falseId));
    ASSERT_EQ (trueId, manager->ite(falseId,falseId,trueId));
    ASSERT_EQ (falseId, manager->ite(trueId,falseId,falseId));
    ASSERT_EQ (trueId, manager->ite(trueId,trueId,trueId));
    ASSERT_EQ (a, manager->ite(a,trueId,falseId));
    ASSERT_EQ (a, manager->ite(falseId,trueId,a));
    ASSERT_EQ (a, manager->ite(trueId,a,falseId));
    ASSERT_EQ (a,manager->ite(b,a,a));
    ASSERT_EQ (falseId,manager->ite(b,falseId,falseId));
    ASSERT_EQ (trueId,manager->ite(b,trueId,trueId));
}

TEST(iteTest, Function) {
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (f,manager->ite(a,b,c));
    ASSERT_EQ (f,manager->ite(a,f,f));
}

TEST (coFactorFalsef, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (c, manager->coFactorFalse(f));
}

//TODO TEST (coFactorTruef, Function)

TEST (coFactorTruef, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (b, manager->coFactorTrue(f));
}

//TODO TEST (coFactorFalsefx, Function)

TEST (coFactorFalsefx, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID d = manager->createVar("d");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (c,manager->coFactorFalse(f,a));
    ASSERT_EQ (manager->ite(a,0,c),manager->coFactorFalse(f,b));
    ASSERT_EQ (manager->ite(a,b,0),manager->coFactorFalse(f,c));
    ASSERT_EQ (f, manager->coFactorFalse(f,d));
}

//TODO TEST (coFactorTruefx, Function)

TEST (coFactorTruefx, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID d = manager->createVar("d");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (b,manager->coFactorTrue(f,a));
    ASSERT_EQ (manager->ite(a,1,c),manager->coFactorTrue(f,b));
    ASSERT_EQ (manager->ite(a,b,1),manager->coFactorTrue(f,c));
    ASSERT_EQ (f, manager->coFactorTrue(f,d));
}

TEST(negTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID a_neg = manager->neg(a);

    ASSERT_EQ (falseId,manager->neg(trueId));
    ASSERT_EQ (trueId,manager->neg(falseId));
    ASSERT_EQ (a, manager->neg(a_neg));

}

TEST(or2Test, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");

    ASSERT_EQ (falseId,manager->or2(falseId,falseId));
    ASSERT_EQ (trueId,manager->or2(falseId,trueId));
    ASSERT_EQ (trueId,manager->or2(trueId,falseId));
    ASSERT_EQ (trueId,manager->or2(trueId,trueId));
    ASSERT_EQ (trueId,manager->or2(a,trueId));
    ASSERT_EQ (a,manager->or2(a,falseId));

}

TEST(and2Test, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");

    ASSERT_EQ (falseId,manager->and2(falseId,falseId));
    ASSERT_EQ (falseId,manager->and2(falseId,trueId));
    ASSERT_EQ (falseId,manager->and2(trueId,falseId));
    ASSERT_EQ (trueId,manager->and2(trueId,trueId));
    ASSERT_EQ (a,manager->and2(a,trueId));
    ASSERT_EQ (falseId,manager->and2(a,falseId));
}

#endif
