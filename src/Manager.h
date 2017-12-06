
#ifndef MANAGER_H
#define MANAGER_H

#include "ManagerInterface.h"
#include <iostream>
#include <set>
#include <vector>

#define BDD_ID_TRUE 1
#define BDD_ID_FALSE 0

using namespace std;
namespace ClassProject {

    typedef struct BDD_Node
    {
        string label;
        BDD_ID top_var;
        BDD_ID high;
        BDD_ID low;
        BDD_ID id;

        BDD_Node() {label = "", top_var = 0; high = 0, low = 0, id = 0;}
        BDD_Node(string label, BDD_ID top_var, BDD_ID high, BDD_ID low, BDD_ID id):label(label), low(low),high(high),top_var(top_var), id(id){}

    } BDD_Node;

    typedef struct BDDComparer {
        bool operator ()(const BDD_Node* node, const BDD_Node* anotherNode) const {
            return (node->top_var < anotherNode->top_var || node->high < anotherNode->high || node->low < anotherNode->low);
        }

    } BDDComparer;

    class Manager : ManagerInterface
    {
       protected:
            std::set<BDD_Node*,BDDComparer> unique_table;
            std::vector<BDD_Node*> pointers;

       public:
            Manager();

            BDD_ID createVar(const std::string &label) override;

            const BDD_ID &True() override;

            const BDD_ID &False() override;

            bool isConstant(const BDD_ID f) override;

            bool isVariable(const BDD_ID x) override;

            BDD_ID topVar(const BDD_ID f) override;

            BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

            BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorTrue(const BDD_ID f) override;

            BDD_ID coFactorFalse(const BDD_ID f) override;

            BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID neg(const BDD_ID a) override;

            //BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

            //std::string getTopVarName(const BDD_ID &root) override;

            //void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

            //void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

            size_t uniqueTableSize() override;

            BDD_Node* getBDDNode(BDD_ID id);

            //void printUniqueTable();

            //bool evaluateBDD(BDD_ID id, std::vector<bool>);
    };

}

#endif
