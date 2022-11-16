// This file needs to be tested without the -std=c++98 compiler flag

#include "../common.hpp"

#ifdef TEST_STD
	#include <type_traits>
#else
	#include "type_traits.hpp"
#endif

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
	print_expr (NS::is_integral<wchar_t>::value);
	print_expr (NS::is_integral<size_t>::value);
	print_expr (NS::is_integral<ptrdiff_t>::value);
	// We can't really have these below, since they're not part of C++98
	/*
	print_expr (NS::is_integral<uint8_t>::value);
	print_expr (NS::is_integral<int8_t>::value);
	print_expr (NS::is_integral<uint16_t>::value);
	print_expr (NS::is_integral<int16_t>::value);
	print_expr (NS::is_integral<uint32_t>::value);
	print_expr (NS::is_integral<int32_t>::value);
	print_expr (NS::is_integral<uint64_t>::value);
	print_expr (NS::is_integral<int64_t>::value);
	*/
}
