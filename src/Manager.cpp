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
        //BDD_Node falseNode("FALSE", BDD_ID_FALSE, BDD_ID_FALSE, BDD_ID_FALSE);
        /*Insert the new node into the uniqueTable*/
        //insertNode(falseNode, BDD_ID_FALSE);

        //! BDD_Node trueNode.
        /*! Initiates the TRUE leaf of node the Binary Tree.*/
        BDD_Node trueNode ("TRUE", BDD_ID_TRUE, BDD_ID_TRUE, BDD_ID_TRUE);
        /*Insert the new node into the uniqueTable*/
        insertNode(trueNode, BDD_ID_TRUE);
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

//! Function to create a new Variable.
/*!
        \param label a string argument.
        \return The id of the new variable which correspond to the size of the uniqueTable.
*/
BDD_ID Manager::createVar(const std::string &label){
    BDD_ID id = (unique_table.size()) << 1;/*! BDD_ID value id. */
    BDD_Node node(label, id, True(), False());/*! BDD_Node value node. */
    insertNode(node,id);
    return id;
}

//! Function to test if a given BDD_ID is a Constant.
/*!
        \param f a BDD_ID argument.
        \return TRUE in case that the given BDD_ID f is a Constant, otherwise return FALSE.
*/
bool Manager::isConstant(const BDD_ID f){
    if(f == False() || f == True())
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
        // 1
        if(i == t)
            return iteST(i,BDD_ID_TRUE,e);

        // 2
        if(i == e)
            return iteST(i,t,BDD_ID_FALSE);

        // 3
        if(i == getComplement(e))
            return iteST(i,t,BDD_ID_TRUE);

        // 4
        if(i == getComplement(t))
        {
            return iteST(i,BDD_ID_FALSE,e);
        }

        return iteST(i,t,e);
    }
}

BDD_ID Manager::getNextId(BDD_ID f)
{
    if(isComplement(f))
        return f+1;
    else
        return f+2;
}


//! Function to compute the IF(BDD_ID i) then(BDD_ID t) ELSE(BDD_ID e) Operator of a given BDD_ID with respect to its top variable.
/*!
        \param i a BDD_ID argument.
        \param t a BDD_ID argument.
        \param e a BDD_ID argument.
        \return Return the id of the computed IF then ELSE Operator.
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

    BDD_ID top_var = topVar(i);

    if(!isTConstant)
    {
        if(topVar(t) < topVar(i))
            top_var = topVar(t);

        if(!isEConstant && topVar(e) < top_var)
            top_var = topVar(e);
    }
    else
    {
        if(topVar(e) < top_var)
            top_var = topVar(e);
    }

    if(top_var != topVar(i) ||
       (top_var == topVar(i) && ((top_var == topVar(t) && i >= getNextId(t)) || (top_var == topVar(e) && i >= getNextId(e)))))
    {
        if(isTConstant)
        {
            //5
            if(t == True())
                return ite(e,t,i,top_var);
            else
            {
                //8
                return ite(getComplement(e),t,getComplement(i),top_var);
            }
        }
        else if(isEConstant)
        {
            //6
            if(e == False())
                return ite(t,i,e,top_var);
            else
            {
                //7
                return ite(getComplement(t),getComplement(i),e);
            }
        }
        else
        {
            //9
            if(e == getComplement(t))
                return ite(t,i,getComplement(i));
        }
    }

    return ite(i,t,e,top_var);

}

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

    /*// 11
    if(isComplement(i))
    {
        //7
        if(e == True() && isComplement(t) && !isConstant(t) && topVar(t) < topVar(i))
            return ite(getComplement(t),getComplement(i),e);

        if(isComplement(e))
        {
            //8
            if(t == False() &&  !isConstant(e) && topVar(e) < topVar(i))
                return ite(getComplement(e),t,getComplement(i));

            // 13 -> 10
            if(isComplement(t))
                return iteC(getComplement(i),getComplement(e),getComplement(t));
        }
        // 11 -> 10
        return ite(getComplement(i),e,t);
    }
    else if(isComplement(t))
    {
        // 4
        if(i == getComplement(t) && !isComplement(e))
            return ite(i,BDD_ID_FALSE,e);

        //12 -> 10
        if(isComplement(e))
        {
            return iteC(i,getComplement(t),getComplement(e));
        }
    }
    else
    {
        // 1
        if(i == t && !isComplement(e))
            return ite(i,BDD_ID_TRUE,e);

        // 2
        if(i == e && !isComplement(e))
            return ite(i,t,BDD_ID_FALSE);

        // 3
        if(i == getComplement(e))
            return ite(i,t,BDD_ID_TRUE);

        // 5
        if(t == True() && !isComplement(e) &&  !isConstant(t) && topVar(e) < topVar(i))
            return ite(e,t,i);

       //6
       if(e == False() && !isConstant(t) && topVar(t) < topVar(i))
           return ite(t,i,e);

        // 9
        if(t == getComplement(e) &&  !isConstant(t) && topVar(t) < topVar(i))
            return ite(t,i,getComplement(i));
    }*/

    BDD_Node iteNode(top_var,t,e);

    auto iteIterator = nodes.find(iteNode);
    if(iteIterator != nodes.end())
    {
        return (*iteIterator).second;
    }

    iteNode.top_var = i;

    iteIterator = computed_table.find(iteNode);
    if(iteIterator != computed_table.end())
    {
        return (*iteIterator).second;
    }


    BDD_ID high = ite(coFactorTrue(i,top_var), coFactorTrue(t,top_var), coFactorTrue(e,top_var));
    BDD_ID low = ite(coFactorFalse(i,top_var), coFactorFalse(t,top_var), coFactorFalse(e,top_var));

    if(high == low)
    {
        return high;
    }

    BDD_ID id = uniqueTableSize() << 1;

    BDD_Node newNode(/*"i" + to_string(id),*/top_var,high,low);

    auto node = nodes.find(newNode);
    if(node == nodes.end())
    {
        insertNode(newNode, id);
        nodes.insert(make_pair(newNode, id));
        if(i != top_var || t != high || e != low)
        {
            computed_table.insert(make_pair(iteNode, id));
        }
        /*else
            cout << "OPS" << endl;*/
        return id;
    }
    else
    {
        id = (*node).second;
        computed_table.insert(make_pair(iteNode, id));
        return id;
    }

    /*if(complement)
    {
        computed_table.insert(make_pair(iteNode, getComplement(id)));
        return getComplement(id);
    }
    else
    {*/


    //}
}

BDD_ID Manager::iteC(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID top_var){
    // Terminal Cases
    if(isConstant(i))
    {
        if(i == BDD_ID_FALSE)
        {
            return getComplement(e);
        }
        else
            return getComplement(t);
    }

    if(t == e)
        return getComplement(t);

    if(t == BDD_ID_TRUE && e == BDD_ID_FALSE)
    {
        return getComplement(i);
    }

    if(t == BDD_ID_FALSE && e == BDD_ID_TRUE)
    {
        return i;
    }   

    /*if(top_var == topVar(i))
    {
        if(!isComplement(i))
        {
            // 1
            if(i == t)
                return iteC(i,BDD_ID_TRUE,e);

            // 2
            if(i == e)
                return iteC(i,t,BDD_ID_FALSE);

            // 3
            if(i == getComplement(e))
                return iteC(i,t,BDD_ID_TRUE);

            // 4
            if(i == getComplement(t))
            {
                return ite(i,BDD_ID_TRUE,getComplement(e));
                //return ite(i,BDD_ID_FALSE,e);
            }
        }
    }
    else if(isConstant(t) || isConstant(e))
    {
        if(!isComplement(i))
        {
            // 5
            if(t == True() && !isComplement(e)/* && top_var == topVar(e)*//*)
            {
                return iteC(e,t,i);
            }
            // 6
            if(e == False() && !isComplement(t)/* && top_var == topVar(t)*//*)
            {
               return iteC(t,i,e);
            }
        }
        else
        {
            // 7
            if(e == True() && isComplement(t))
                return iteC(getComplement(t),getComplement(i),e);

            // 8
            if(t == False() && isComplement(e))
            {
                return ite(getComplement(e),True(),i);
                //return ite(getComplement(e),t,getComplement(i));
            }
        }
    }
    else if(!isComplement(i) && !isComplement(t) && e == getComplement(t))
    {
        return iteC(t,i,getComplement(i));
    }*/


    if(isComplement(i))
    {
        if(isComplement(e))
            return ite(getComplement(i),getComplement(e),getComplement(t));
        return iteC(getComplement(i),e,t,top_var);
    }
    else if(isComplement(t))
    {
        return ite(i,getComplement(t),getComplement(e),top_var);
    }

    /*// 1
    if(i == t)
        return iteC(i,BDD_ID_TRUE,e);

    // 2
    if(i == e)
        return iteC(i,t,BDD_ID_FALSE);

    // 3
    if(i == getComplement(e))
        return iteC(i,t,BDD_ID_TRUE);

    // 4
    if(i == getComplement(t))
        return iteC(i,BDD_ID_FALSE,e);

    // 5
    if(t == True() &&  topVar(e) < topVar(i))
        return iteC(e,t,i);

    // 6
    if(e == False() && topVar(t) < topVar(i))
       return iteC(t,i,e);

    // 7
    if(e == True() && isComplement(t) && isComplement(i) &&  topVar(t) < topVar(i))
        return iteC(getComplement(t),getComplement(i),e);

    // 8
    if(t == False() && isComplement(e) && isComplement(i) && topVar(e) < topVar(i))
        return iteC(getComplement(e),t,getComplement(i));

    // 9
    if(t == getComplement(e) && topVar(t) < topVar(i))
        return iteC(t,i,getComplement(i));

    if(isComplement(i))
    {
        if(isComplement(e))
            return ite(getComplement(i),getComplement(e),getComplement(t));
        return iteC(getComplement(i),e,t);
    }
    else if(isComplement(t))
    {
        return ite(i,getComplement(t),getComplement(e));
    }*/



    /*// 11
    if(isComplement(i))
    {
        //7
        if(e == True() && isComplement(t) &&  !isConstant(t) && topVar(t) < topVar(i))
            return iteC(getComplement(t),getComplement(i),e);

        if(isComplement(e))
        {
            //8
            if(t == False() &&  !isConstant(e) && topVar(e) < topVar(i))
                return iteC(getComplement(e),t,getComplement(i));

            // 13 -> 10
            if(isComplement(t))
                return ite(getComplement(i),getComplement(e),getComplement(t));
        }
        // 11 -> 10
        return iteC(getComplement(i),e,t);
    }
    else if(isComplement(t))
    {
        // 4
        if(i == getComplement(t) && !isComplement(e))
            return iteC(i,BDD_ID_FALSE,e);

        //12 -> 10
        if(isComplement(e))
        {
            return ite(i,getComplement(t),getComplement(e));
        }
    }
    else
    {
        // 1
        if(i == t )//&& !isComplement(e))
            return iteC(i,BDD_ID_TRUE,e);

        // 2
        if(i == e )//&& !isComplement(e))
            return iteC(i,t,BDD_ID_FALSE);

        // 3
        if(i == getComplement(e))
            return iteC(i,t,BDD_ID_TRUE);

        // 5
        if(t == True() && !isComplement(e) && !isConstant(e) &&  topVar(e) < topVar(i))
            return iteC(e,t,i);

       //6
       if(e == False() &&  !isConstant(t) && topVar(t) < topVar(i))
           return iteC(t,i,e);

        // 9
        if(t == getComplement(e) && topVar(t) < topVar(i))
            return iteC(t,i,getComplement(i));
    }*/

    BDD_Node iteNode(top_var,t,e);

    auto iteIterator = nodes.find(iteNode);
    if(iteIterator != nodes.end())
        return getComplement((*iteIterator).second);

    iteNode.top_var = i;

    iteIterator = computed_table.find(iteNode);
    if(iteIterator != computed_table.end())
        return getComplement((*iteIterator).second);

    /*BDD_ID top_var = topVar(i);

    if(!isConstant(t) && topVar(t) < top_var)
    {
        top_var = topVar(t);
    };

    if(!isConstant(e) && topVar(e) < top_var)
    {
        top_var = topVar(e);
    }*/

    BDD_ID high = ite(coFactorTrue(i,top_var), coFactorTrue(t,top_var), coFactorTrue(e,top_var));
    BDD_ID low = ite(coFactorFalse(i,top_var), coFactorFalse(t,top_var), coFactorFalse(e,top_var));


    if(high == low)
    {
        return getComplement(high);
    }

    BDD_ID id = ((uniqueTableSize()) << 1);

    BDD_Node newNode(/*"i" + to_string(id),*/top_var,high,low);

    auto node = nodes.find(newNode);
    if(node == nodes.end())
    {
        insertNode(newNode, id);
        nodes.insert(make_pair(newNode, id));
        if(i != top_var || t != high || e != low)
            computed_table.insert(make_pair(iteNode, id));
        /*else
            cout << "OPS" << endl;*/
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
    if(isConstant(f) || isConstant(x) || /*(!isTheSameVar && isVariable(f)) ||*/ topVarF > x)
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
    if(isConstant(f) || isConstant(x) || /*(!isTheSameVar && isVariable(f)) ||*/  topVarF > x)
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


//! Function to print all the BDD_Nodes present in the uniqueTable.
/*!
*/
void Manager::printUniqueTable(){
    cout<< "unique_table" << endl;
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

    cout<< "computed_table" << endl;
    for(auto& node : computed_table)
    {
        cout<< " ID = " << node.second
             << " TOP_VAR = " << node.first.top_var
             << " HIGH = " << node.first.high
             << " LOW = " << node.first.low
             << " LABEL = " << node.first.label << endl;
    }
}

void Manager::insertNode(BDD_Node& node, BDD_ID id)
{
    unique_table.push_back(node);
    //pointers.push_back(node);
}
