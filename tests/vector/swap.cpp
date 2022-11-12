#include "common.hpp"

int main()
{
	NS::vector<int> vec1 (10, 100);
	NS::vector<int> vec2 (10, 200);

	print_vector (vec1);
	print_vector (vec2);

	vec1.swap (vec2);
	
	print_vector (vec1);
	print_vector (vec2);
}
