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

const BDD_ID& Manager::True()
{
    return pointers[BDD_ID_TRUE]->id;
}

size_t Manager::uniqueTableSize()
{
    return unique_table.size();
}

BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID id = unique_table.size();
    BDD_Node* node = new BDD_Node(label, id, True(), False(), id);
    unique_table.insert(node);
    pointers.push_back(node);
    cout << id << endl;
    return id;
}

BDD_Node* Manager::getBDDNode(BDD_ID id)
{
    BDD_Node* node = pointers[id];
    std::cout << node->top_var << node->high << node->low << endl;
    return node;
}


