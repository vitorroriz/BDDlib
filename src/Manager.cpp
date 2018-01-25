#include "Manager.h"

using namespace ClassProject;

//! Manager Class
/*!
        Implements the virtual functions from the ManagerInterface.
*/

//! Manager Constructor.
/*
        Initiates the Manager class by creating two BDD_Nodes(FALSE,TRUE) that represents the leaf nodes of the Binary Tree.
*/
Manager::Manager(){
        /*Creating terminal vars */
        //! BDD_Node falseNode.
        /*! Initiates the FALSE leaf node of the Binary Tree.*/
        BDD_Node falseNode("FALSE", BDD_ID_FALSE, BDD_ID_FALSE, BDD_ID_FALSE);
        /*Insert the new node into the uniqueTable*/
        insertNode(falseNode);

        //! BDD_Node trueNode.
        /*! Initiates the TRUE leaf of node the Binary Tree.*/
        BDD_Node trueNode ("TRUE", BDD_ID_TRUE, BDD_ID_TRUE, BDD_ID_TRUE);
        /*Insert the new node into the uniqueTable*/
        insertNode(trueNode);
}

//! Function to return the id of the FALSE leaf node in the Binary Tree.
/*!
        \return The id of the False leaf node in the Binary Tree.
*/
const BDD_ID& Manager::False(){
    return (*unique_table.find(getBDDNode(BDD_ID_FALSE))).second;
}

//! Function to return the id of the TRUE leaf node in the Binary Tree.
/*!
        \return The id of the TRUE leaf node in the Binary Tree.
*/
const BDD_ID& Manager::True(){
    return (*unique_table.find(getBDDNode(BDD_ID_TRUE))).second;
}

//! Function to return the size of the uniqueTable.
/*!
        \return The size_t of the uniqueTable.
*/
size_t Manager::uniqueTableSize(){
    return unique_table.size();
}

//! Function to create a new Variable.
/*!
        \param label a string argument.
        \return The id of the new variable which correspond to the size of the uniqueTable.
*/
BDD_ID Manager::createVar(const std::string &label){
    BDD_ID id = unique_table.size();/*! BDD_ID value id. */
    BDD_Node node(label, id, True(), False());/*! BDD_Node value node. */
    insertNode(node);
    return id;
}

//! Function to test if a given BDD_ID is a Constant.
/*!
        \param f a BDD_ID argument.
        \return TRUE in case that the given BDD_ID f is a Constant, otherwise return FALSE.
*/
bool Manager::isConstant(const BDD_ID f){
    if(f == BDD_ID_FALSE || f == BDD_ID_TRUE)
        return true;
    return false;
}

//! Function to test if a given BDD_ID is a Variable.
/*!
        \param x a BDD_ID argument.
        \return TRUE in case that the given BDD_ID x is a Variable, otherwise return FALSE.
*/
bool Manager::isVariable(const BDD_ID x){
    BDD_Node node = getBDDNode(x);/*!< BDD_Node pointer value node.*/
    if(!isConstant(x) && (node.top_var == x))
        return true;
    return false;
}

//! Function to return the top variable of a given BDD_ID.
/*!
        \param f a BDD_ID argument.
        \return Return the top variable of the given BDD_ID.
*/
BDD_ID  Manager::topVar(const BDD_ID f){
    return getBDDNode(f).top_var;
}

//! Function to compute the IF(BDD_ID i) then(BDD_ID t) ELSE(BDD_ID e) Operator of a given BDD_ID with respect to its top variable.
/*!
        \param i a BDD_ID argument.
        \param t a BDD_ID argument.
        \param e a BDD_ID argument.
        \return Return the id of the computed IF then ELSE Operator.
*/
BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e){
    BDD_ID ite_t = t;
    BDD_ID ite_e = e;

    if(i == t)
       ite_t  = BDD_ID_TRUE;
    if(i == e)
        ite_e = BDD_ID_FALSE;

    if(isConstant(i))
    {
        if(i == BDD_ID_FALSE)
            return e;
        return t;
    }

    if(t == BDD_ID_TRUE && e == BDD_ID_FALSE)
        return i;

    if(t == e)
        return t;

    ITE_Node iteNode(i,ite_t,ite_e);

    auto iteIterator = computed_table.find(iteNode);

    if(iteIterator != computed_table.end())
        return (*iteIterator).second;

    BDD_ID top_var = topVar(i);

    if(!isConstant(t) && topVar(t) < top_var)
        top_var = topVar(t);

    if(!isConstant(e) && topVar(e) < top_var)
        top_var = topVar(e);

    BDD_ID high = ite(coFactorTrue(i,top_var), coFactorTrue(t,top_var), coFactorTrue(e,top_var));

    BDD_ID low = ite(coFactorFalse(i,top_var), coFactorFalse(t,top_var), coFactorFalse(e,top_var));

    if(high == low)
        return high;

    BDD_ID id = uniqueTableSize();
    BDD_Node newNode("f" + to_string(id),top_var,high,low);

    auto node = unique_table.find(newNode);
    if(node == unique_table.end())
    {
        insertNode(newNode);
    }
    else
    {
        id = (*node).second;
    }

    computed_table.insert(make_pair(iteNode, id));

    return id;
}

//! Function to compute the FALSE coFactor of a given BDD_ID f.
/*!
        \param f a BDD_ID argument.
        \return Return the FALSE coFactor of the given BDD_ID f.
*/
BDD_ID Manager::coFactorFalse(const BDD_ID f){
    return getBDDNode(f).low;
}

//! Function to compute the FALSE coFactor of a given BDD_ID f with respect to BDD_ID x.
/*!
        \param f a BDD_ID argument.
        \param x a BDD_ID argument.
        \return Return the computed ITE operator of the TRUE, and FALSE branches of BDD_ID f with respect to BDD_ID x.
*/
BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x){
    bool isTheSameVar = topVar(f) == x;/*! bool value isTheSameVar.*/
    if(isConstant(f) || isConstant(x) || /* (!isTheSameVar && isVariable(f)) || */ topVar(f) > x)
        return f;
    if(isTheSameVar)
        return getBDDNode(f).low;

    BDD_ID high = coFactorFalse(getBDDNode(f).high,x);
    BDD_ID low = coFactorFalse(getBDDNode(f).low,x);

    return ite(topVar(f),high,low);
}

//! Function to compute the TRUE coFactor of a given BDD_ID f.
/*!
        \param f a BDD_ID argument.
        \return Return the TRUE coFactor of the given BDD_ID f.
*/
BDD_ID Manager::coFactorTrue(const BDD_ID f){
    return getBDDNode(f).high;
}

//! Function to compute the TRUE coFactor of a given BDD_ID f with respect to BDD_ID x.
/*!
        \param f a BDD_ID argument.
        \param x a BDD_ID argument.
        \return Return the computed ITE operator of the TRUE, and FALSE branches of BDD_ID f with respect to BDD_ID x.
*/
BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x){
    bool isTheSameVar = topVar(f) == x;/*! bool value isTheSameVar.*/
    if(isConstant(f) || isConstant(x) || /* (!isTheSameVar && isVariable(f)) || */ topVar(f) > x)
        return f;
    if(isTheSameVar)
        return getBDDNode(f).high;

    BDD_ID high = coFactorTrue(getBDDNode(f).high,x);
    BDD_ID low = coFactorTrue(getBDDNode(f).low,x);

    return ite(topVar(f),high,low);
}

//! Function to compute an AND Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.
        \return Return the computed ITE operator of BDD_IDs a and b according to the AND Function.
*/
BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b){
    return ite(a,b,BDD_ID_FALSE);
}

//! Function to compute an OR Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.
        \return Return the computed ITE operator of BDD_IDs a and b according to the OR Function.
*/
BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b){
    return ite(a,BDD_ID_TRUE,b);
}

//! Function to compute an XOR Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.
        \return Return the computed ITE operator of BDD_IDs a and b according to the XOR Function.
*/
BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b){
    return ite(a,neg(b),b);
}

//! Function to compute the Negation of a given BDD_ID.
/*!
        \param a a BDD_ID argument.
        \return Return the Negation of a given BDD_ID.
*/
BDD_ID Manager::neg(const BDD_ID a){
    ite(a,BDD_ID_FALSE,BDD_ID_TRUE);
}

//! Function to compute a NAND Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.
        \return Return the computed ITE operator of BDD_IDs a and b according to the NAND Function.
*/
BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b){
    ite(a,neg(b),BDD_ID_TRUE);
}

//! Function to compute a NOR Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.
        \return Return the computed ITE operator of BDD_IDs a and b according to the NOR Function.
*/
BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b){
    ite(a,BDD_ID_FALSE,neg(b));
}


//! Function to get the name of the Top Variable of a given BDD_ID.
/*!
        \param root a BDD_ID argument.
        \return Return the label(Top Varaible Name) of the given BDD_ID root.
*/
std::string Manager::getTopVarName(const BDD_ID &root)
{
    return getBDDNode(getBDDNode(root).top_var).label;
}

//! Function to find out all the reachable nodes in the Binary Tree starting from a given BDD_ID.
/*!
        \param root a BDD_ID argument.
        \return Return set containing all the reachable Nodes from a given Node.
*/
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    if(!isConstant(root))
    {
            findNodes(coFactorFalse(root), nodes_of_root);
            findNodes(coFactorTrue(root), nodes_of_root);
    }
    nodes_of_root.insert(root);
}

//! Function to find out all the reachable Variables in the Binary Tree starting from a given BDD_ID.
/*!
        \param root a BDD_ID argument.
        \return Return set containing all the reachable Variables from a given Node.
*/
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    if(!isConstant(root))
    {
        findVars(coFactorFalse(root), vars_of_root);
        findVars(coFactorTrue(root), vars_of_root);
        vars_of_root.insert(topVar(root));
    }
}

//! Function to return a BDD_Node from the uniqueTable according to its BDD_ID.
/*!
        \param id a BDD_ID argument.
        \return Return a BDD_Node from the uniqueTable that has the corresponding BDD_ID.
*/
const BDD_Node& Manager::getBDDNode(BDD_ID id){
    return pointers[id];
}

//! Function to print all the BDD_Nodes present in the uniqueTable.
/*!
*/
void Manager::printUniqueTable(){
    for(auto& node : unique_table)
    {
        cout << "ID = " << node.second
             << " TOP_VAR = " << node.first.top_var
             << " HIGH = " << node.first.high
             << " LOW = " << node.first.low
             << " LABEL = " << node.first.label << endl;
    }
}

void Manager::insertNode(BDD_Node &node)
{
    unique_table.insert(make_pair(node,uniqueTableSize()));
    pointers.push_back(node);
}
