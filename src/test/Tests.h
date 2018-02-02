
#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#define GTEST_HAS_TR1_TUPLE 0
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
    ASSERT_EQ (1, manager->uniqueTableSize());
}

TEST (uniqueTableSizeTest, Variable) {
    Manager *manager = new Manager();
    manager->createVar("a");
    ASSERT_EQ (2, manager->uniqueTableSize());
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

    ASSERT_EQ (5, size1);
    ASSERT_EQ (size1,size2);
}

TEST (createVarTest, varAttributes) {
    Manager *manager = new Manager();
    BDD_ID id = manager->createVar("a");
    BDD_Node var = manager->getBDDNode(id);
    ASSERT_EQ ("a", var.label);
    ASSERT_EQ (id, var.top_var);
    ASSERT_EQ (manager->True(), var.high);
    ASSERT_EQ (manager->False(), var.low);
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
    BDD_ID g = manager->ite(b,c,a);
    BDD_ID h = manager->ite(c,b,a);

    ASSERT_EQ (a, manager->getBDDNode(f).top_var);
    ASSERT_EQ (a, manager->getBDDNode(g).top_var);
    ASSERT_EQ (a, manager->getBDDNode(h).top_var);
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
    BDD_ID g = manager->ite(b,c,d);

    ASSERT_EQ (c,manager->coFactorFalse(f,a));
    ASSERT_EQ (manager->ite(a,0,c),manager->coFactorFalse(f,b));
    ASSERT_EQ (manager->ite(a,b,0),manager->coFactorFalse(f,c));
    ASSERT_EQ (f, manager->coFactorFalse(f,d));
    ASSERT_EQ (g, manager->coFactorFalse(g,a));
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
    BDD_ID g = manager->ite(b,c,d);

    ASSERT_EQ (b,manager->coFactorTrue(f,a));
    ASSERT_EQ (manager->ite(a,1,c),manager->coFactorTrue(f,b));
    ASSERT_EQ (manager->ite(a,b,1),manager->coFactorTrue(f,c));
    ASSERT_EQ (f, manager->coFactorTrue(f,d));
    ASSERT_EQ (g, manager->coFactorTrue(g,a));

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
    ASSERT_EQ(manager->ite(a,b,falseId),manager->ite(b,a,falseId));
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
    BDD_ID b = manager->createVar("b");
    BDD_ID nega = manager->neg(a);

    ASSERT_EQ (falseId,manager->xor2(falseId,falseId));
    ASSERT_EQ (trueId,manager->xor2(falseId,trueId));
    ASSERT_EQ (trueId,manager->xor2(trueId,falseId));
    ASSERT_EQ (falseId,manager->xor2(trueId,trueId));
    ASSERT_EQ (nega,manager->xor2(a,trueId));
    ASSERT_EQ (a,manager->xor2(a,falseId));
    ASSERT_EQ (manager->neg(manager->xor2(a,b)),manager->ite(a,b,manager->neg(b)));
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

TEST(getTopVarNameTest, Variable)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");


    ASSERT_EQ ("a",manager->getTopVarName(a));
    ASSERT_EQ ("b",manager->getTopVarName(b));
}

TEST(getTopVarNameTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID f = manager->ite(a,b,c);

    ASSERT_EQ ("a",manager->getTopVarName(f));
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

TEST(ComplementEdgesTest, LeafNode)
{
    Manager *manager = new Manager();
    BDD_ID trueId = manager->True();
    BDD_ID falseId = manager->False();

    ASSERT_EQ (falseId,manager->neg(trueId));
    ASSERT_EQ (trueId,manager->neg(falseId));
    ASSERT_EQ (trueId,manager->neg(manager->neg(trueId)));
    ASSERT_EQ (falseId,manager->neg(manager->neg(falseId)));
}

TEST(ComplementEdgesTest, Variable)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");

    ASSERT_EQ (a+1,manager->neg(a));
}

TEST(ComplementEdgesTest, Function)
{
    Manager *manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");

    BDD_ID F = manager->or2(manager->and2(a,b),manager->and2(manager->neg(a),c));
    BDD_ID G = manager->or2(manager->and2(a,manager->neg(b)),manager->and2(manager->neg(a),manager->neg(c)));

    ASSERT_EQ (manager->neg(F),G);
}

TEST(StandardTriplesTest, Function)
{
    Manager* manager = new Manager();

    BDD_ID falseNode = manager->False();
    BDD_ID trueNode = manager->True();

    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID d = manager->createVar("d");

    BDD_ID F = manager->and2(manager->and2(a,b),c);
    BDD_ID negF = manager->neg(F);
    BDD_ID G = manager->or2(manager->or2(a,b),c);
    BDD_ID negG = manager->neg(G);

    ASSERT_EQ (manager->ite(F,F,G),manager->ite(F,trueNode,G));
    ASSERT_EQ (manager->ite(F,G,F),manager->ite(F,G,falseNode));
    ASSERT_EQ (manager->ite(F,G,negF),manager->ite(F,G,trueNode));
    ASSERT_EQ (manager->ite(F,negF,G),manager->ite(F,falseNode,G));

    //topVar(F) == topVar(G)
    ASSERT_EQ (manager->ite(F,trueNode,G),manager->ite(G,trueNode,F));
    ASSERT_EQ (manager->ite(F,G,falseNode),manager->ite(G,F,falseNode));
    ASSERT_EQ (manager->ite(F,G,trueNode),manager->ite(negG,negF,trueNode));
    ASSERT_EQ (manager->ite(F,falseNode,G),manager->ite(negG,falseNode,negF));
    ASSERT_EQ (manager->ite(F,G,negG),manager->ite(G,F,negF));

    G = manager->or2(manager->or2(b,c),d);
    negG = manager->neg(G);

    //topVar(F) != topVar(G)
    ASSERT_EQ (manager->ite(F,trueNode,G),manager->ite(G,trueNode,F));
    ASSERT_EQ (manager->ite(F,G,falseNode),manager->ite(G,F,falseNode));
    ASSERT_EQ (manager->ite(F,G,trueNode),manager->ite(negG,negF,trueNode));
    ASSERT_EQ (manager->ite(F,falseNode,G),manager->ite(negG,falseNode,negF));
    ASSERT_EQ (manager->ite(F,G,negG),manager->ite(G,F,negF));

    BDD_ID H = manager->xor2(manager->xor2(a,c),d);
    BDD_ID negH = manager->neg(H);

    ASSERT_EQ (manager->ite(F,G,H),manager->ite(negF,H,G));
    ASSERT_EQ (manager->ite(F,G,H),manager->neg(manager->ite(F,negG,negH)));
    ASSERT_EQ (manager->ite(F,G,H),manager->neg(manager->ite(negF,negH,negG)));
}

TEST(XOR3Test, Function)
{
    Manager* manager = new Manager();
    BDD_ID a = manager->createVar("a");
    BDD_ID b = manager->createVar("b");
    BDD_ID c = manager->createVar("c");
    BDD_ID XORab = manager->xor2(a,b);
    BDD_ID XORabc = manager->xor2(XORab,c);

    ASSERT_EQ (manager->ite(c,manager->neg(XORab),XORab),XORabc);
    ASSERT_EQ (manager->neg(manager->xor2(c,b)),manager->coFactorTrue(XORabc,a));
    ASSERT_EQ (manager->neg(manager->xor2(c,a)),manager->coFactorTrue(XORabc,b));
    ASSERT_EQ (manager->neg(manager->xor2(b,a)),manager->coFactorTrue(XORabc,c));
    ASSERT_EQ (manager->xor2(c,b),manager->coFactorFalse(XORabc,a));
    ASSERT_EQ (manager->xor2(c,a),manager->coFactorFalse(XORabc,b));
    ASSERT_EQ (manager->xor2(b,a),manager->coFactorFalse(XORabc,c));
}

#endif
