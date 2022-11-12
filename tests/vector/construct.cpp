#include "common.hpp"

void test_int ()
{
	// ~~ Default
	NS::vector<int> vec1;
	print_vector (vec1);
	
	// ~~ count + value
	// This also tests that there is no ambiguity with the iterator range constructor
	NS::vector<int> vec2 (10, 12);
	print_vector (vec2);

	// ~~ Copy
	NS::vector<int> vec3 (vec2);
	print_vector (vec3);

	std::list<int> lst;
	for (int i = 0; i < 10; i++)
		lst.push_front (i);

	// ~~ Iterator range
	NS::vector<int> vec4 (lst.begin (), lst.end ());
	print_vector (vec4);
}

void test_string ()
{
	// ~~ Default
	NS::vector<std::string> vec1;
	print_vector (vec1);
	
	// ~~ count + value
	// This also tests that there is no ambiguity with the iterator range constructor
	NS::vector<std::string> vec2 (10, "I am a default value");
	print_vector (vec2);

	// ~~ Copy
	NS::vector<std::string> vec3 (vec2);
	print_vector (vec3);

	std::list<std::string> lst;
	for (int i = 0; i < 10; i++)
		lst.push_back ("Hello Sailor!");

	// ~~ Iterator range
	NS::vector<std::string> vec4 (lst.begin (), lst.end ());
	print_vector (vec4);
}

int main()
{
	std::cout << "=== Int tests\n" << std::endl;
	test_int ();
	std::cout << "\n=== String tests\n" << std::endl;
	test_string ();
}
