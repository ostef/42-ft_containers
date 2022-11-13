#include "common.hpp"
#include <vector>

template<typename Container>
void all_tests ()
{
	Container cnt;
	for (int i = 0; i < 10; i++)
		cnt.push_back (i);

	NS::stack<int, Container> stk (cnt);
	stk.push (10);
	stk.push (11);
	stk.push (12);
	
	print_expr (stk.empty ());
	print_expr (stk.size ());

	stk.pop ();

	print_expr (stk.empty ());
	print_expr (stk.size ());

	NS::stack<int, Container> other (cnt);

	print_expr (stk == other);
	print_expr (stk != other);
	print_expr (stk < other);
	print_expr (stk <= other);
	print_expr (stk > other);
	print_expr (stk >= other);
}

int main()
{
	std::cout << "\n=== std::list<int> ===\n" << std::endl;
	all_tests<std::list<int> > ();
	std::cout << "\n=== std::vector<int> ===\n" << std::endl;
	all_tests<std::vector<int> > ();
}
