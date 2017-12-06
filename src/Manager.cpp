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
    return id;
}

bool Manager::isConstant(const BDD_ID f)
{
    if(f == True() || f == False())
        return true;
    return false;
}


bool Manager::isVariable(const BDD_ID x)
{
    BDD_Node* node = getBDDNode(x);
    if(!isConstant(x) && (node->top_var == node->id))
        return true;
    return false;
}

BDD_ID  Manager::topVar(const BDD_ID f)
{
    return getBDDNode(f)->top_var;
}

BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e)
{
    BDD_ID top_var = topVar(i);

    if(isConstant(i))
    {
        if(i == BDD_ID_FALSE)
            return e;
        return t;
    }

    if(isVariable(i) && t == BDD_ID_TRUE && t == BDD_ID_FALSE)
        return i;

    if(t == e)
        return t;

    BDD_ID high = ite(coFactorTrue(i), coFactorTrue(t,top_var), coFactorTrue(e,top_var));

    BDD_ID low = ite(coFactorFalse(i), coFactorFalse(t,top_var), coFactorFalse(e,top_var));

    if(high == low)
        return high;

    BDD_Node* node = new BDD_Node("f" + to_string(uniqueTableSize()-2),top_var,high,low,uniqueTableSize());
    auto it = unique_table.insert(node);

    if(it.second)
    {
        pointers.push_back(*(it.first));
    }

    return (*(it.first))->id;
}

BDD_ID Manager::coFactorFalse(const BDD_ID f)
{
    return getBDDNode(f)->low;
}

BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x)
{
    bool isTheSameVar = topVar(f) == x;
    if(isConstant(f) || isConstant(x) || !isVariable(x) || (!isTheSameVar && isVariable(f)))
        return f;
    if(isTheSameVar)
        return getBDDNode(f)->low;

    BDD_ID high = coFactorFalse(getBDDNode(f)->high,x);
    BDD_ID low = coFactorFalse(getBDDNode(f)->low,x);

    return ite(topVar(f),high,low);
}

BDD_ID Manager::coFactorTrue(const BDD_ID f)
{
    return getBDDNode(f)->high;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x)
{
    bool isTheSameVar = topVar(f) == x;
    if(isConstant(f) || isConstant(x) || !isVariable(x) || (!isTheSameVar && isVariable(f)))
        return f;
    if(isTheSameVar)
        return getBDDNode(f)->high;

    BDD_ID high = coFactorTrue(getBDDNode(f)->high,x);
    BDD_ID low = coFactorTrue(getBDDNode(f)->low,x);

    return ite(topVar(f),high,low);
}

BDD_ID Manager::neg(const BDD_ID a)
{
    ite(a,BDD_ID_FALSE,BDD_ID_TRUE);
}

BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b)
{
    return ite(a,BDD_ID_TRUE,b);
}

BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b)
{
    return ite(a,b,BDD_ID_FALSE);
}

BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b)
{
    return ite(a,neg(b),b);
}

BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b)
{
    ite(a,BDD_ID_FALSE,neg(b));
}

BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b)
{
    ite(a,neg(b),BDD_ID_TRUE);
}

std::string Manager::getTopVarName(const BDD_ID &root)
{
    return getBDDNode(root)->label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root)
{
    if(!isConstant(root))
    {
        findNodes(coFactorFalse(root), nodes_of_root);
        findNodes(coFactorTrue(root), nodes_of_root);
    }
    nodes_of_root.insert(root);
}

BDD_Node* Manager::getBDDNode(BDD_ID id)
{
    return pointers[id];
}
