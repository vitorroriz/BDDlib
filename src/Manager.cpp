#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
        /*Creating terminal vars */

        BDD_Node* falseNode = new BDD_Node("FALSE", BDD_ID_FALSE, BDD_ID_FALSE, BDD_ID_FALSE, BDD_ID_FALSE);
        unique_table.insert(falseNode);
        pointers.push_back(falseNode);
        BDD_Node* trueNode = new BDD_Node("TRUE", BDD_ID_TRUE, BDD_ID_TRUE, BDD_ID_TRUE, BDD_ID_TRUE);
        unique_table.insert(trueNode);
        pointers.push_back(trueNode);

        std::cout << "Manager obj created" << std::endl;
}

const BDD_ID& Manager::False()
{
    return  pointers[BDD_ID_FALSE]->id;
}


