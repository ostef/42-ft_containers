#include "common.hpp"

int main()
{
	NS::map<std::string, int> map1;
	map1.insert (NS::make_pair ("Stefan", 20));
	map1.insert (NS::make_pair ("Nina", 23));
	map1.insert (NS::make_pair ("Louis", 21));
	map1.insert (NS::make_pair ("Paul", 23));

	print_map (map1);

	NS::map<std::string, int> map2 (map1);

	print_map (map2);

	NS::map<std::string, int> map3 (map1.begin (), ++(++map1.begin ()));

	print_map (map3);
}
