#include "../common.hpp"
#include <type_traits>

int main()
{
	print_expr (NS::is_integral<NS::vector<int> >::value);
	print_expr (NS::is_integral<const char *>::value);
	print_expr (NS::is_integral<char>::value);
	print_expr (NS::is_integral<unsigned char>::value);
	print_expr (NS::is_integral<short>::value);
	print_expr (NS::is_integral<unsigned short>::value);
	print_expr (NS::is_integral<int>::value);
	print_expr (NS::is_integral<unsigned int>::value);
	print_expr (NS::is_integral<long>::value);
	print_expr (NS::is_integral<unsigned long>::value);
	print_expr (NS::is_integral<long long>::value);
	print_expr (NS::is_integral<unsigned long long>::value);
	print_expr (NS::is_integral<const int>::value);
	print_expr (NS::is_integral<int &>::value);
	print_expr (NS::is_integral<const int &>::value);
	print_expr (NS::is_integral<volatile int>::value);
	print_expr (NS::is_integral<volatile long>::value);
}
