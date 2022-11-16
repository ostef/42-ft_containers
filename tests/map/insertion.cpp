#include "common.hpp"

int main()
{
	typedef NS::map<std::string, int>::iterator iterator;

	NS::map<std::string, int> map1;
	NS::pair<iterator, bool> it1 = map1.insert (NS::make_pair ("Stefan", 20));
	NS::pair<iterator, bool> it2 = map1.insert (NS::make_pair ("Nina", 23));
	NS::pair<iterator, bool> it3 = map1.insert (NS::make_pair ("Louis", 21));
	NS::pair<iterator, bool> it4 = map1.insert (NS::make_pair ("Paul", 23));
	NS::pair<iterator, bool> it5 = map1.insert (NS::make_pair ("Stefan", 21));

	print_map (map1);
	print_expr (it1.second);
	print_expr (std::distance (map1.begin (), it1.first));
	print_expr (it2.second);
	print_expr (std::distance (map1.begin (), it2.first));
	print_expr (it3.second);
	print_expr (std::distance (map1.begin (), it3.first));
	print_expr (it4.second);
	print_expr (std::distance (map1.begin (), it4.first));
	print_expr (it5.second);
	print_expr (std::distance (map1.begin (), it5.first));
	print_expr (ensure_balance_factor_correctness (map1));
}
