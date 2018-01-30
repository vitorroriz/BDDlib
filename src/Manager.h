
#ifndef MANAGER_H
#define MANAGER_H

#include "ManagerInterface.h"
#include <iostream>
#include <unordered_map>
#include <vector>

#define BDD_ID_TRUE 1
#define BDD_ID_FALSE 0

#define CACHE_SIZE 2048

using namespace std;
namespace ClassProject {

    //! typedef struct BDD_Node
    /*!
      Custom data type representing a BDD_Node.
    */

    typedef struct BDD_Node{
        string label;/*! String value label. */
        BDD_ID top_var;/*! BDD_ID value top_var. */
        BDD_ID high;/*! BDD_ID of high Node. */
        BDD_ID low;/*! BDD_ID of low Node. */

        BDD_Node() {label = "", top_var = 0; high = 0, low = 0;}
        BDD_Node(string label, BDD_ID top_var, BDD_ID high, BDD_ID low):label(label), low(low),high(high),top_var(top_var){}
        BDD_Node(BDD_ID top_var, BDD_ID high, BDD_ID low):label(""), low(low),high(high),top_var(top_var){}

    } BDD_Node;

    //! typedef struct BDDComparer
    /*!
      Necessary struct for comparing the elements of the unique_table.
    */
    typedef struct BDDComparer {
        bool operator ()(const BDD_Node& node, const BDD_Node& anotherNode) const {
            return (node.high == anotherNode.high && node.low == anotherNode.low && node.top_var == anotherNode.top_var);
        }
    } BDDComparer;


    //! typedef struct BDDHasher
    /*!
      Necessary struct for organizing the elements of the unique_table.
    */
    typedef struct BDDHasher
    {
            std::size_t operator()(const BDD_Node& node) const
            {
                BDD_ID seed = 0;
                seed ^= hash<BDD_ID>()(node.low) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= hash<BDD_ID>()(node.high) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= hash<BDD_ID>()(node.top_var) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
                //return ((hash<BDD_ID>()(node.low) ^ (hash<BDD_ID>()(node.high) <<1)) >>1) ^ (hash<BDD_ID>()(node.top_var) << 1);
            }
    } BDDHasher;

    //! Manager Class.
    /*!
      Declaration of the functions from the ManagerInterface.
    */
    class Manager : public ManagerInterface
    {
       private:
            BDD_ID falseNode = BDD_ID_FALSE;
            BDD_ID trueNode = BDD_ID_TRUE;
            vector<BDD_Node> unique_table;/*! Unordered Map that represents the unique_table.*/
            //vector<BDD_Node> pointers;
            unordered_map<BDD_Node,BDD_ID,BDDHasher,BDDComparer> nodes;
            unordered_map<BDD_Node,BDD_ID,BDDHasher,BDDComparer> computed_table;

       public:
            Manager();

            BDD_ID createVar(const std::string &label) override;

            const BDD_ID &True() override;

            const BDD_ID &False() override;

            bool isConstant(const BDD_ID f) override;

            bool isVariable(const BDD_ID x) override;

            BDD_ID topVar(const BDD_ID f) override;

            BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

            BDD_ID iteST(const BDD_ID i, const BDD_ID t, const BDD_ID e);

            BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e, const BDD_ID top_var);

            BDD_ID iteC(const BDD_ID i, const BDD_ID t, const BDD_ID e, const BDD_ID top_var);

            BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorTrueC(const BDD_ID f, BDD_ID x);

            BDD_ID coFactorFalseC(const BDD_ID f, BDD_ID x);

            BDD_ID coFactorTrue(const BDD_ID f) override;

            BDD_ID coFactorFalse(const BDD_ID f) override;

            BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID neg(const BDD_ID a) override;

            BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

            BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

            std::string getTopVarName(const BDD_ID &root) override;

            void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

            void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

            size_t uniqueTableSize() override;

            const BDD_Node& getBDDNode(BDD_ID id);

            void printUniqueTable();

            void insertNode(BDD_Node& node, BDD_ID id);

            BDD_ID getComplement(BDD_ID f);

            bool isComplement(BDD_ID f);

            BDD_ID getNextId(BDD_ID f);
    };
}

#endif


