#include "common.hpp"
#include <vector>

int main ()
{
	typedef NS::map<std::string, int>::iterator iterator;
	
	std::vector<iterator> it1;
	std::vector<iterator> it2;

	NS::map<std::string, int> map1;
	map1.insert (NS::make_pair ("Stefan", 20));
	map1.insert (NS::make_pair ("Nina", 23));
	map1.insert (NS::make_pair ("Louis", 21));
	map1.insert (NS::make_pair ("Paul", 23));
	for (iterator it = map1.begin (); it != map1.end (); it++)
		it1.push_back (it);

	NS::map<std::string, int> map2;
	map2.insert (NS::make_pair ("Martin", 24));
	map2.insert (NS::make_pair ("Clementine", 28));
	map2.insert (NS::make_pair ("Maxime", 23));
	for (iterator it = map2.begin (); it != map2.end (); it++)
		it2.push_back (it);

	print_map (map1);
	print_map (map2);

	map1.swap (map2);

	print_map (map1);
	print_map (map2);

	size_t i = 0;
	for (iterator it = map1.begin (); it != map1.end (); it++, i++)
	{
		print_expr (it == it2[i]);
	}

	std::cout << std::endl;

	i = 0;
	for (iterator it = map2.begin (); it != map2.end (); it++, i++)
	{
		print_expr (it == it1[i]);
	}

}
