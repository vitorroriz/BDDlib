/*=============================================================================
    Written by Mohammad R Fadiheh (2017)
=============================================================================*/

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<map>

struct node {
	std::string var_name;
        int var_id;
	int low;
	int high;
};

typedef std::map<int, node> uniqueTable;

bool isEquivalent(uniqueTable* BDD1, uniqueTable* BDD2, int root1, int root2)
{
	if(BDD1->find(root1) == BDD1->end() || BDD2->find(root2) == BDD2->end())
		return false;
	if(root1 == 1 && root2 == 1)
		return true;
	if(root1 == 0 && root2 == 0)
		return true;
	if(root1 != root2 && ( (root1 == 0 || root1 == 1) || (root2 == 0 || root2 == 1) ) )
		return false;
	if(BDD1->at(root1).var_id != BDD2->at(root2).var_id)
		return false;
	return isEquivalent(BDD1, BDD2, BDD1->at(root1).low, BDD2->at(root2).low) and isEquivalent(BDD1, BDD2, BDD1->at(root1).high, BDD2->at(root2).high);
}

bool textToUniqueTable(std::string filename, uniqueTable* BDD)
{
	std::ifstream BDD_if(filename.c_str());

	if(!BDD_if.is_open())
	{
		std::cout << "invalid file!" << std::endl;
		return false;
	}

	std::stringstream ss;

	std::string temp;
	std::string var_name;
	int id, top_var;

	while(!BDD_if.eof())
	{

		node n;			
		temp.clear();
		std::getline(BDD_if, temp,'\n');
		if(temp.find("Terminal Node: 1") != std::string::npos)
		{
			n.var_name = "";
			n.low = 1;
			n.high = 1;
			BDD->insert(std::pair<int,node>(1,n));
		}
		else if(temp.find("Terminal Node: 0") != std::string::npos)
		{
			n.var_name = "";
			n.low = 0;
			n.high = 0;
			BDD->insert(std::pair<int,node>(0,n));

		}
		else if(temp.find("Variable Node:") != std::string::npos)
		{
			ss.clear();
			ss.str(temp);
			ss>>temp>>temp>>id>>temp>>temp>>temp>>n.var_id>>temp>>temp>>temp>>n.var_name>>temp>>n.low>>temp>>n.high;
			BDD->insert(std::pair<int,node>(id,n));
		}
	}

	if( BDD->size() == 0)
	{
		std::cout<<"invalid file"<< std::endl;
		return false;
	}

	return true;


}

int main(int argc, char* argv[])
{

	/* Number of arguments validation */
	if (3 > argc)
	{
		std::cout << "Must specify a filename!" << std::endl;
		return -1;
	}
	
	uniqueTable* BDD1 = new uniqueTable;
	uniqueTable* BDD2 = new uniqueTable;

	std::string BDD1_file = argv[1];
	std::string BDD2_file = argv[2];

	if( !textToUniqueTable(BDD1_file, BDD1) || !textToUniqueTable(BDD2_file, BDD2) )
	{
		return -1;
	}

	if( isEquivalent(BDD1, BDD2, BDD1->rbegin()->first, BDD2->rbegin()->first) )
		std::cout<<"Equivalent!"<<std::endl;
	else
		std::cout<<"Not Equivalent!"<<std::endl;
	return 0;
}

