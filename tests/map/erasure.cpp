#include "common.hpp"

int main()
{
	typedef NS::map<std::string, int>::iterator iterator;

	NS::map<std::string, int> map1;
	iterator it1 = map1.insert (NS::make_pair ("Stefan", 20)).first;
	iterator it2 = map1.insert (NS::make_pair ("Nina", 23)).first;
	iterator it3 = map1.insert (NS::make_pair ("Louis", 21)).first;
	iterator it4 = map1.insert (NS::make_pair ("Paul", 23)).first;

	print_map (map1);

	map1.erase (it1);
	print_map (map1);
	
	map1.erase (it2);
	print_map (map1);

	map1.erase (it3, it4);
	print_map (map1);
}
