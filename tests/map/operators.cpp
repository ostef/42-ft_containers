#include "common.hpp"

int main()
{
	NS::map<std::string, int> map1;
	map1.insert (NS::make_pair ("Stefan", 20));
	map1.insert (NS::make_pair ("Nina", 23));
	map1.insert (NS::make_pair ("Louis", 21));
	map1.insert (NS::make_pair ("Paul", 23));

	NS::map<std::string, int> map2 (map1);

	NS::map<std::string, int> map3;
	map3.insert (NS::make_pair ("Martin", 24));
	map3.insert (NS::make_pair ("Clementine", 28));
	map3.insert (NS::make_pair ("Maxime", 23));

	NS::map<std::string, int> map4;
	map4.insert (NS::make_pair ("Jeremy", 24));
	map4.insert (NS::make_pair ("Maxime", 26));
	map4.insert (NS::make_pair ("Theo", 20));
	map4.insert (NS::make_pair ("Wati-Theo", 21));

	print_map (map1);
	print_map (map2);
	print_map (map3);
	print_map (map4);

	print_expr (map1 == map2);
	print_expr (map1 != map2);
	print_expr (map1 < map2);
	print_expr (map1 > map2);
	print_expr (map1 <= map2);
	print_expr (map1 >= map2);

	print_expr (map1 == map3);
	print_expr (map1 != map3);
	print_expr (map1 < map3);
	print_expr (map1 > map3);
	print_expr (map1 <= map3);
	print_expr (map1 >= map3);

	print_expr (map3 == map1);
	print_expr (map3 != map1);
	print_expr (map3 < map1);
	print_expr (map3 > map1);
	print_expr (map3 <= map1);
	print_expr (map3 >= map1);

	print_expr (map1 == map4);
	print_expr (map1 != map4);
	print_expr (map1 < map4);
	print_expr (map1 > map4);
	print_expr (map1 <= map4);
	print_expr (map1 >= map4);
}
