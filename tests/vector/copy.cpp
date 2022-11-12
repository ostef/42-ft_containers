#include "common.hpp"

int main()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back (i);

	print_vector (vec1);

	NS::vector<int> vec2;
	for (int i = 5; i > 0; i--)
		vec2.push_back (i);
		
	print_vector (vec2);

	NS::vector<int> vec3 (vec1);

	print_vector (vec3);
	
	vec3 = vec2;
	
	print_vector (vec3);
}
