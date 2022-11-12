#include "common.hpp"

void test_push_back()
{
	NS::vector<int> vec1;
	vec1.push_back (10);
	vec1.push_back (11);
	vec1.push_back (12);
	
	print_vector (vec1);
	
	vec1.push_back (0);
	vec1.push_back (1);
	vec1.push_back (2);
	
	print_vector (vec1);
}

void test_pop_back()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back (i);
	
	print_vector (vec1);

	for (int i = 0; i < 5; i++)
		vec1.pop_back ();

	print_vector (vec1);
}

void test_insert()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back (i);

	print_vector (vec1);

	vec1.insert (vec1.begin () + 2, 50);

	print_vector (vec1);

	vec1.insert (vec1.end () - 5, 3, 69);

	print_vector (vec1);

	std::list<int> lst;
	for (int i = 100; i < 120; i++)
		lst.push_back (i);

	vec1.insert (vec1.end (), lst.begin (), lst.end ());
	print_vector (vec1);
}

void test_erase()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back (i);
	
	NS::vector<int>::iterator it1 = vec1.erase (vec1.begin ());

	print_vector (vec1);
	std::cout << "it1 is " << (it1 - vec1.begin ()) << std::endl;

	NS::vector<int>::iterator it2 = vec1.erase (vec1.begin () + 1, vec1.end () - 1);

	print_vector (vec1);
	std::cout << "it2 is " << (it2 - vec1.begin ()) << std::endl;
}

int main()
{
	std::cout << "\n=== push_back ===\n" << std::endl;
	test_push_back ();
	
	std::cout << "\n=== pop_back ===\n" << std::endl;
	test_pop_back ();
	
	std::cout << "\n=== insert ===\n" << std::endl;
	test_insert ();
	
	std::cout << "\n=== erase ===\n" << std::endl;
	test_erase ();
}
