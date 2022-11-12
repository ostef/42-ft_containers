#include "common.hpp"

#define print_iter(map, it) {\
	if (it == map.end ())\
		std::cout << #it " == end ()" << std::endl;\
	else\
		std::cout << #it " == " << it->first << " : " << it->second << ", dist == " << std::distance (map.begin (), it) << std::endl;\
	}

void test_find (NS::map<std::string, int> &map)
{
	typedef NS::map<std::string, int>::iterator iterator;

	iterator it1 = map.find ("Stefan");
	print_iter (map, it1);

	iterator it2 = map.find ("Maxime");
	print_iter (map, it2);

	iterator it3 = map.find ("Paul");
	print_iter (map, it3);
}

void test_find_const (const NS::map<std::string, int> &map)
{
	typedef NS::map<std::string, int>::const_iterator iterator;

	iterator it1 = map.find ("Stefan");
	print_iter (map, it1);

	iterator it2 = map.find ("Maxime");
	print_iter (map, it2);

	iterator it3 = map.find ("Paul");
	print_iter (map, it3);
}

void test_bounds (NS::map<std::string, int> &map)
{
	typedef NS::map<std::string, int>::iterator iterator;

	iterator it1_lower = map.lower_bound ("Stefan");
	print_iter (map, it1_lower);
	iterator it1_upper = map.upper_bound ("Stefan");
	print_iter (map, it1_upper);
	print_expr (std::distance (it1_lower, it1_upper));

	iterator it2_lower = map.lower_bound ("Maxime");
	print_iter (map, it2_lower);
	iterator it2_upper = map.upper_bound ("Maxime");
	print_iter (map, it2_upper);
	print_expr (std::distance (it2_lower, it2_upper));

	iterator it3_lower = map.lower_bound ("Paul");
	print_iter (map, it3_lower);
	iterator it3_upper = map.upper_bound ("Paul");
	print_iter (map, it3_upper);
	print_expr (std::distance (it3_lower, it3_upper));
}

void test_bounds_const (const NS::map<std::string, int> &map)
{
	typedef NS::map<std::string, int>::const_iterator iterator;

	iterator it1_lower = map.lower_bound ("Stefan");
	print_iter (map, it1_lower);
	iterator it1_upper = map.upper_bound ("Stefan");
	print_iter (map, it1_upper);
	print_expr (std::distance (it1_lower, it1_upper));

	iterator it2_lower = map.lower_bound ("Maxime");
	print_iter (map, it2_lower);
	iterator it2_upper = map.upper_bound ("Maxime");
	print_iter (map, it2_upper);
	print_expr (std::distance (it2_lower, it2_upper));

	iterator it3_lower = map.lower_bound ("Paul");
	print_iter (map, it3_lower);
	iterator it3_upper = map.upper_bound ("Paul");
	print_iter (map, it3_upper);
	print_expr (std::distance (it3_lower, it3_upper));
}

int main ()
{
	NS::map<std::string, int> map1;
	map1.insert (NS::make_pair ("Stefan", 20));
	map1.insert (NS::make_pair ("Nina", 23));
	map1.insert (NS::make_pair ("Louis", 21));
	map1.insert (NS::make_pair ("Paul", 23));

	test_find (map1);
	std::cout << std::endl;
	
	test_find_const (map1);
	std::cout << std::endl;

	test_bounds (map1);
	std::cout << std::endl;

	test_bounds_const (map1);
	std::cout << std::endl;
}
