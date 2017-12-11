
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

using namespace ClassProject;

TEST (FalseTest, FalseID) {
    Manager *manager = new Manager();
    ASSERT_EQ (BDD_ID_FALSE, manager->False());
}

TEST (TrueTest, TrueID) {
    Manager *manager = new Manager();
    ASSERT_EQ (BDD_ID_TRUE, manager->True());
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

TEST (topVarTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (a, manager->getBDDNode(f)->top_var);
}

TEST (coFactorFalsefxTest, TerminalCase) {
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

TEST (coFactorFalsefxTest, Function)
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

TEST (coFactorFalsefTest, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (manager->False(), manager->coFactorFalse(id));
}

TEST (coFactorFalsefTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (c, manager->coFactorFalse(f));
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

TEST (coFactorTruef, Variable) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    ASSERT_EQ (manager->True(), manager->coFactorTrue(id));
}

TEST (coFactorTruef, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ (b, manager->coFactorTrue(f));
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

TEST(negTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID nega = manager->neg(a);

    ASSERT_EQ (falseId,manager->neg(trueId));
    ASSERT_EQ (trueId,manager->neg(falseId));
    ASSERT_EQ (a, manager->neg(nega));

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

TEST(xor2Test, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID nega = manager->neg(a);

    ASSERT_EQ (falseId,manager->xor2(falseId,falseId));
    ASSERT_EQ (trueId,manager->xor2(falseId,trueId));
    ASSERT_EQ (trueId,manager->xor2(trueId,falseId));
    ASSERT_EQ (falseId,manager->xor2(trueId,trueId));
    ASSERT_EQ (nega,manager->xor2(a,trueId));
    ASSERT_EQ (a,manager->xor2(a,falseId));
}

TEST(nor2Test, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID nega = manager->neg(a);

    ASSERT_EQ (trueId,manager->nor2(falseId,falseId));
    ASSERT_EQ (falseId,manager->nor2(falseId,trueId));
    ASSERT_EQ (falseId,manager->nor2(trueId,falseId));
    ASSERT_EQ (falseId,manager->nor2(trueId,trueId));
    ASSERT_EQ (falseId,manager->nor2(a,trueId));
    ASSERT_EQ (nega,manager->nor2(a,falseId));
    ASSERT_EQ (manager->neg(manager->or2(a,b)),manager->nor2(a,b));
}

TEST(nand2Test, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID nega = manager->neg(a);

    ASSERT_EQ (trueId,manager->nand2(falseId,falseId));
    ASSERT_EQ (trueId,manager->nand2(falseId,trueId));
    ASSERT_EQ (trueId,manager->nand2(trueId,falseId));
    ASSERT_EQ (falseId,manager->nand2(trueId,trueId));
    ASSERT_EQ (nega,manager->nand2(a,trueId));
    ASSERT_EQ (trueId,manager->nand2(a,falseId));
    ASSERT_EQ (manager->neg(manager->and2(a,b)),manager->nand2(a,b));

}

TEST(getTopVarNameTest, Function)
{
    Manager *manager = new Manager();
    BDD_Node* nodeA = manager->getBDDNode(manager->createVar("a"));
    BDD_Node* nodeNegA = manager->getBDDNode(manager->neg(nodeA->id));

    ASSERT_EQ ("a",nodeA->label);
    ASSERT_EQ ("f1",nodeNegA->label);
}

TEST(findNodesTest, LeafNode)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    std::set<BDD_ID> nodesFound;
    manager->findNodes(trueId,nodesFound);
    manager->findNodes(falseId,nodesFound);
    std::set<BDD_ID> nodes = {trueId,falseId};

    ASSERT_EQ (nodes,nodesFound);
}


TEST(findNodesTest, Variable)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    std::set<BDD_ID> nodesFound;
    manager->findNodes(a,nodesFound);
    std::set<BDD_ID> nodes = {a, trueId, falseId};

    ASSERT_EQ (nodes,nodesFound);
}

TEST(findNodesTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID d = manager->createVar("d");
    BDD_ID f = manager->and2(manager->or2(a,b),
                      manager->and2(c,d));
    std::set<BDD_ID> nodesFound;
    manager->findNodes(f,nodesFound);
    std::set<BDD_ID> nodes = {f,manager->ite(b,manager->ite(c,d,falseId),falseId),manager->ite(c,d,falseId),d,trueId,falseId};

    ASSERT_EQ (nodes,nodesFound);
}

TEST(findVarsTest, LeafNode)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    std::set<BDD_ID> varsFound;
    manager->findVars(trueId,varsFound);
    manager->findVars(falseId,varsFound);
    std::set<BDD_ID> vars = {};

    ASSERT_EQ (vars,varsFound);
}

TEST(findVarsTest, Variable)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    std::set<BDD_ID> varsFound;
    manager->findVars(a,varsFound);
    std::set<BDD_ID> vars = {a};

    ASSERT_EQ (vars,varsFound);
}

TEST(findVarsTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID d = manager->createVar("d");
    BDD_ID f = manager->or2(manager->and2(a,b),
                      manager->and2(c,d));
    std::set<BDD_ID> varsFound;
    manager->findVars(f,varsFound);
    std::set<BDD_ID> vars = {a,b,c,d};

    ASSERT_EQ (vars,varsFound);
}
#endif
