#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
	/*Creating terminal vars */
//	ID_Nodes.push_back(&(*(ID_Table.insert(BDD_Nodes(ID_Nodes.size(), 0, 0, "0")).first)));
//	ID_Nodes.push_back(&(*(ID_Table.insert(BDD_Nodes(ID_Nodes.size(), 1, 1, "1")).first)));
        std::cout << "Manager obj created" << std::endl;
}
/*
const &BDD_ID Manager::True()
{
	return BDD_ID_HIGH;
}

const &BDD_ID Manager::False()
{
	return BDD_ID_LOW;
}

BDD_ID Manager::createVar(const std::string &label)
{

	BDD_Node node = BDD_Node(ID_Nodes.size(), True(), False(), label);
	ID_Nodes.push_back(&(*(ID_Table.insert(node).first)));
}    
*/
