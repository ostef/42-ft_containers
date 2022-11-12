#include "common.hpp"

int main()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back (i);

	NS::vector<int> vec2;
	for (int i = 0; i < 10; i++)
		vec2.push_back (10 - i);

	NS::vector<int> vec3;

	NS::vector<int> vec4 (vec1);

	print_vector (vec1);
	print_vector (vec2);
	print_vector (vec3);
	print_vector (vec4);

	print_expr (vec1 == vec2);
	print_expr (vec1 != vec2);
	print_expr (vec1 < vec2);
	print_expr (vec1 > vec2);
	print_expr (vec1 <= vec2);
	print_expr (vec1 >= vec2);

	print_expr (vec1 == vec3);
	print_expr (vec1 != vec3);
	print_expr (vec1 < vec3);
	print_expr (vec1 > vec3);
	print_expr (vec1 <= vec3);
	print_expr (vec1 >= vec3);

	print_expr (vec3 == vec1);
	print_expr (vec3 != vec1);
	print_expr (vec3 < vec1);
	print_expr (vec3 > vec1);
	print_expr (vec3 <= vec1);
	print_expr (vec3 >= vec1);

	print_expr (vec1 == vec4);
	print_expr (vec1 != vec4);
	print_expr (vec1 < vec4);
	print_expr (vec1 > vec4);
	print_expr (vec1 <= vec4);
	print_expr (vec1 >= vec4);
}
