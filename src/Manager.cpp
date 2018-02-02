#include "Manager.h"

using namespace ClassProject;

//! Manager Class
/*!
        Implements the virtual functions from the ManagerInterface.
*/

//! Manager Constructor.
/*
        Initiates the Manager class by creating the BDD_Node(TRUE) that represents the leaf node of the Binary Tree.
*/
Manager::Manager(){
        /*Creating terminal var */
        //! BDD_Node trueNode.
        /*! Initiates the TRUE leaf of node the Binary Tree.*/
        BDD_Node trueNode ("TRUE", BDD_ID_TRUE, BDD_ID_TRUE, BDD_ID_TRUE);
        /*Insert the new node into the uniqueTable*/
        unique_table.push_back(trueNode);
}

//! Function to return the id of the FALSE leaf node in the Binary Tree.
/*!
        \return The id of the False leaf node in the Binary Tree.
*/
const BDD_ID& Manager::False(){
    return falseNode;
}

//! Function to return the id of the TRUE leaf node in the Binary Tree.
/*!
        \return The id of the TRUE leaf node in the Binary Tree.
*/
const BDD_ID& Manager::True(){
    return trueNode;
}

//! Function to return the size of the uniqueTable.
/*!
        \return The size_t of the uniqueTable.
*/
size_t Manager::uniqueTableSize(){
    return unique_table.size();
}

//! Function to return the size of the new_nodes.
/*!
	\return the size of new_nodes. 
*/
size_t Manager::newNodesSize(){
    return new_nodes.size();
}

//! Function to return the size of the Computed Table.
/*!
	\return the size of computed_table.
*/
size_t Manager::computedTableSize(){
    return computed_table.size();
}

//! Function to create a new Variable.
/*!
        \param label a string argument.
        \return The id of the new variable which correspond to the size of the uniqueTable.
*/
BDD_ID Manager::createVar(const std::string &label){
    BDD_ID id = (unique_table.size()) << 1;/*! BDD_ID value id. */
    BDD_Node var(label, id, BDD_ID_TRUE, BDD_ID_FALSE);/*! BDD_Node value var. */
    unique_table.push_back(var);
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

//! Function to return the coplement of a given BDD_ID.
/*!
	\param f a BDD_ID argument.
	\return BDD_ID_TRUE or FALSE if f is a constant, otherwise return the BDD_ID of f +1 if BDD_ID is even, or BDD_ID -1 if it's odd. 
*/
BDD_ID Manager::getComplement(BDD_ID f)
{
    if(isConstant(f))
    {
        if(f == BDD_ID_FALSE)
            return BDD_ID_TRUE;
        else
            return BDD_ID_FALSE;
    }

    if(f % 2 == 0)
        return f+1;
    else
         return f-1;
}

//! Function check if a given BDD_ID is a complement of a previous BDD_ID.
/*!
	\param f a BDD_ID argument.
	\return TRUE in the case of f be a complent BDD_ID, otherwise return FALSE.
*/
bool Manager::isComplement(BDD_ID f)
{
    if(isConstant(f))
    {
        if(f == BDD_ID_FALSE)
            return true;
        else
            return false;
    }
    if(f % 2 == 1)
        return true;
    return false;
}

//! Function to compute the IF(BDD_ID i) then(BDD_ID t) ELSE(BDD_ID e) Operator.
/*!
        \param i a BDD_ID argument.
        \param t a BDD_ID argument.
        \param e a BDD_ID argument.
        \return Return the id of the computed IF then ELSE Operator.
*/
BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e)
{
    // Terminal Cases
    if(isConstant(i))
    {
        if(i == BDD_ID_FALSE)
            return e;
        return t;
    }

    if(t == e)
        return t;

    if(t == BDD_ID_TRUE && e == BDD_ID_FALSE)
    {
        return i;
    }

    if(t == BDD_ID_FALSE && e == BDD_ID_TRUE)
    {
        return getComplement(i);
    }

    if(!isConstant(t) && !isConstant(e)
       && i != t && i != getComplement(t) && t != e && t != getComplement(e) && i != e && i != getComplement(e))
    {
        BDD_ID top_var = topVar(i);

        if(topVar(t) < top_var)
            top_var = topVar(t);

        if(topVar(e) < top_var)
            top_var = topVar(e);

        return ite(i,t,e,top_var);
    }
    else
    {
        if(i == t)
            return iteST(i,BDD_ID_TRUE,e);

        if(i == e)
            return iteST(i,t,BDD_ID_FALSE);

        if(i == getComplement(e))
            return iteST(i,t,BDD_ID_TRUE);

        if(i == getComplement(t))
        {
            return iteST(i,BDD_ID_FALSE,e);
        }

        return iteST(i,t,e);
    }
}

//! Function to get the next ID of a given BDD_ID.
/*!
	\param f a BDD_ID argument.
	\return the next BDD_ID of f.
*/
BDD_ID Manager::getNextId(BDD_ID f)
{
    if(isComplement(f))
        return f+1;
    else
        return f+2;
}

//! Function to compute the ite according to the standard triples.
/*!
	\param i a BDD_ID argument.
	\param t a BDD_ID argument.
	\param e a BDD_ID argument.
        \return the ID of the computed IF THEN ELSE operator according to the standard triples.
*/  
BDD_ID Manager::iteST(const BDD_ID i, const BDD_ID t, const BDD_ID e)
{
    if(t == e)
        return t;

    if(t == BDD_ID_TRUE && e == BDD_ID_FALSE)
    {
        return i;
    }

    if(t == BDD_ID_FALSE && e == BDD_ID_TRUE)
    {
        return getComplement(i);
    }

    bool isTConstant = isConstant(t);
    bool isEConstant = isConstant(e);

    BDD_ID topVarI = topVar(i);
    BDD_ID topVarT = topVar(t);
    BDD_ID topVarE = topVar(e);

    BDD_ID top_var = topVarI;

    if(!isTConstant)
    {        
        if(topVarT < top_var)
            top_var = topVarT;

        if(!isEConstant && topVarE < top_var)
            top_var = topVarE;
    }
    else
    {
        if(topVarE < top_var)
            top_var = topVarE;
    }

    if(top_var != topVarI ||
       (top_var == topVarI && ((top_var == topVarT && i >= getNextId(t)) || (top_var == topVarE && i >= getNextId(e)))))
    {
        if(isTConstant)
        {
            if(t == BDD_ID_TRUE)
                return ite(e,t,i,top_var);
            else
            {
                return ite(getComplement(e),t,getComplement(i),top_var);
            }
        }
        else if(isEConstant)
        {
            if(e == BDD_ID_FALSE)
                return ite(t,i,e,top_var);
            else
            {
                return ite(getComplement(t),getComplement(i),e,top_var);
            }
        }
        else
        {
            if(e == getComplement(t))
                return ite(t,i,getComplement(i),top_var);
        }
    }

    return ite(i,t,e,top_var);
}

//! Function to compute the IF(BDD_ID i) then(BDD_ID t) ELSE(BDD_ID e) Operator of a given BDD_ID with respect to its top variable.
/*!
        \param i a BDD_ID argument.
        \param t a BDD_ID argument.
        \param e a BDD_ID argument.
	\param top_var a BDD_ID argument.
        \return Return the id of the computed IF then ELSE Operator.
*/
BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID top_var){

    if(t == e)
        return t;

    if(t == BDD_ID_TRUE && e == BDD_ID_FALSE)
    {
        return i;
    }

    if(t == BDD_ID_FALSE && e == BDD_ID_TRUE)
    {
        return getComplement(i);
    }

    if(isComplement(i))
    {
        if(isComplement(e))
            return iteC(getComplement(i),getComplement(e),getComplement(t),top_var);
        return ite(getComplement(i),e,t,top_var);
    }
    else if(isComplement(t))
    {
        return iteC(i,getComplement(t),getComplement(e),top_var);
    }

    BDD_Node iteNode(i,t,e);

    if(i == top_var)
    {
        auto node = new_nodes.find(iteNode);
        if(node != new_nodes.end())
        {
            return (*node).second;
        }
    }

    auto node = computed_table.find(iteNode);
    if(node != computed_table.end())
    {
        return (*node).second;
    }

    BDD_ID high = ite(coFactorTrue(i,top_var),coFactorTrue(t,top_var),coFactorTrue(e,top_var));
    BDD_ID low = ite(coFactorFalse(i,top_var),coFactorFalse(t,top_var),coFactorFalse(e,top_var));

    if(high == low)
    {
        return high;
    }

    BDD_ID id = uniqueTableSize() << 1;

    BDD_Node newNode(top_var,high,low);

    node = new_nodes.find(newNode);
    if(node == new_nodes.end())
    {
        unique_table.push_back(newNode);
        new_nodes.insert(make_pair(newNode, id));
        if(i != top_var || t != high || e != low)
        {
            computed_table.insert(make_pair(iteNode, id));
        }
        return id;
    }
    else
    {
        id = (*node).second;
        computed_table.insert(make_pair(iteNode, id));
        return id;
    }
}

//! Function to compute the COMPLEMENT IF(BDD_ID i) then(BDD_ID t) ELSE(BDD_ID e) Operator of a given BDD_ID with respect to its top variable.
/*!
        \param i a BDD_ID argument.
        \param t a BDD_ID argument.
        \param e a BDD_ID argument.
	\param top_var a BDD_ID argument.
        \return Return the id of the computed IF then ELSE Operator.
*/
BDD_ID Manager::iteC(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID top_var){
    BDD_Node iteNode(i,t,e);

    if(i == top_var)
    {
        auto node = new_nodes.find(iteNode);
        if(node != new_nodes.end())
            return getComplement((*node).second);
    }

    auto node = computed_table.find(iteNode);
    if(node != computed_table.end())
        return getComplement((*node).second);

    BDD_ID high = ite(coFactorTrue(i,top_var),coFactorTrue(t,top_var),coFactorTrue(e,top_var));
    BDD_ID low = ite(coFactorFalse(i,top_var),coFactorFalse(t,top_var),coFactorFalse(e,top_var));

    if(high == low)
    {
        return getComplement(high);
    }

    BDD_ID id = ((uniqueTableSize()) << 1);

    BDD_Node newNode(top_var,high,low);

    node = new_nodes.find(newNode);
    if(node == new_nodes.end())
    {
        unique_table.push_back(newNode);
        new_nodes.insert(make_pair(newNode, id));
        if(i != top_var || t != high || e != low)
            computed_table.insert(make_pair(iteNode, id));
    }
    else
    {
        id = (*node).second;
        computed_table.insert(make_pair(iteNode, id));
    }

    return getComplement(id);
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
    BDD_ID topVarF = topVar(f);
    if(isConstant(f) || isConstant(x) || topVarF > x)
    {
        return f;
    }

    BDD_ID low = coFactorFalse(f);

    if(topVarF == x)
    {
        if(isComplement(f))
            return getComplement(low);
        else
            return low;
    }

    BDD_ID high = coFactorTrue(f);


    if(isComplement(f))
        return getComplement(ite(topVarF,coFactorFalse(high,x),coFactorFalse(low,x)));
    else
        return ite(topVarF,coFactorFalse(high,x),coFactorFalse(low,x));
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
    BDD_ID topVarF = topVar(f);
    if(isConstant(f) || isConstant(x) || topVarF > x)
        return f;

    BDD_ID high = coFactorTrue(f);

    if(topVarF == x)
    {
        if(isComplement(f))
            return getComplement(high);
        else
            return high;
    }

    BDD_ID low = coFactorFalse(f);

    if(isComplement(f))
    {
        return getComplement(ite(topVarF,coFactorTrue(high,x),coFactorTrue(low,x)));
    }
    else
        return ite(topVarF,coFactorTrue(high,x),coFactorTrue(low,x));
}

//! Function to compute an AND Boolean Function of two given BDD_IDs a and b.
/*!
        \param a a BDD_ID argument.
        \param b a BDD_ID argument.id
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
    if(!isConstant(root) && root%2 == 1)
    {
        nodes_of_root.insert(root);
        return findNodes(root-1,nodes_of_root);
    }

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
    if(isConstant(id))
        return unique_table[0];
    else
        return unique_table[(id >> 1)];
}


//! Function to print all the BDD_Nodes present in the uniqueTable, new_nodes table and in the computed table.
/*!
*/
void Manager::printUniqueTable(){
    cout<< "Unique Table:" << endl;
    BDD_ID i = 0;
    BDD_Node node = unique_table[i];
    cout << " ID = " << ++i
         << " TOP_VAR = " << node.top_var
         << " HIGH = " << node.high
         << " LOW = " << node.low
         << " LABEL = " << node.label << endl;
    for(;i < unique_table.size(); i++)
    {
        node = unique_table[i];
        cout << " ID = " << i*2
             << " TOP_VAR = " << node.top_var
             << " HIGH = " << node.high
             << " LOW = " << node.low
             << " LABEL = " << node.label << endl;
    }

    cout<< "Computed Table:" << endl;
    for(auto& node : computed_table)
    {
        cout<< " ID = " << node.second
             << " TOP_VAR = " << node.first.top_var
             << " HIGH = " << node.first.high
             << " LOW = " << node.first.low
             << " LABEL = " << node.first.label << endl;
    }

    cout<< "New Nodes" << endl;
    for(auto& node : new_nodes)
    {
        cout<< " ID = " << node.second
             << " TOP_VAR = " << node.first.top_var
             << " HIGH = " << node.first.high
             << " LOW = " << node.first.low
             << " LABEL = " << node.first.label << endl;
    }
}
