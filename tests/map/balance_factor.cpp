#include "common.hpp"

int main()
{
	NS::map<int, int> map1;

	map1.insert (NS::make_pair (10, 10));
	map1.insert (NS::make_pair (20, 20));
	map1.insert (NS::make_pair (30, 30));
	map1.insert (NS::make_pair (40, 40));
	
	print_expr (ensure_balance_factor_correctness (map1));
	
	map1.insert (NS::make_pair (7, 7));
	map1.insert (NS::make_pair (9, 9));
	map1.insert (NS::make_pair (8, 8));
	map1.insert (NS::make_pair (6, 6));
	
	print_expr (ensure_balance_factor_correctness (map1));
	
	map1.insert (NS::make_pair (22, 22));
	map1.insert (NS::make_pair (22, 22));
	
	print_expr (ensure_balance_factor_correctness (map1));

	map1.erase (10);
	map1.erase (1);
	map1.erase (6);
	map1.erase (7);
	map1.erase (20);
	map1.erase (30);
	
	print_expr (ensure_balance_factor_correctness (map1));

	for (int i = 0; i < 1000; i++)
	{
		int val = rand () % 5000;
		map1.insert (NS::make_pair (val, val));
	}

	print_expr (ensure_balance_factor_correctness (map1));

	int erased = 0;
	for (int i = 0; erased < 100; i++)
	{
		erased += (int)map1.erase (i);
	}

	print_expr (ensure_balance_factor_correctness (map1));
}
