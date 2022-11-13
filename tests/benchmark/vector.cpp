#include "common.hpp"

#define TESTED_TYPE std::string

void test_push (NS::vector<TESTED_TYPE> &vec, size_t n)
{
	benchmark bench ("push");

	TESTED_TYPE val;

	bench.start ();
	for (size_t i = 0; i < n; i++)
	{
		vec.push_back (val);
	}
	bench.end (n);

	std::cout << bench << std::endl;
}

void test_pop (NS::vector<TESTED_TYPE> &vec, size_t n)
{
	benchmark bench ("pop");

	if (n > vec.size ())
		n = vec.size ();

	bench.start ();
	for (size_t i = 0; i < n; i++)
	{
		vec.pop_back ();
	}
	bench.end (n);

	std::cout << bench << std::endl;
}

void test_insert (NS::vector<TESTED_TYPE> &vec, size_t n)
{
	benchmark bench ("insert");

	TESTED_TYPE val;

	bench.start ();
	for (size_t i = 0; i < n; i++)
	{
		NS::vector<TESTED_TYPE>::iterator it = vec.begin () + (rand () % (vec.size () + 1));
		vec.insert (it, val);
	}
	bench.end (n);

	std::cout << bench << std::endl;
}

void test_erase (NS::vector<TESTED_TYPE> &vec, size_t n)
{
	benchmark bench ("erase");

	if (n > vec.size ())
		n = vec.size ();

	bench.start ();
	for (size_t i = 0; i < n; i++)
	{
		NS::vector<TESTED_TYPE>::iterator it = vec.begin () + (rand () % vec.size ());
		vec.erase (it);
	}
	bench.end (n);

	std::cout << bench << std::endl;
}

int main ()
{
	NS::vector<TESTED_TYPE> vec;

	test_push (vec, 10);
	test_pop (vec, 10);
	test_insert (vec, 10);
	test_erase (vec, 10);

	std::cout << std::endl;

	test_push (vec, 100);
	test_pop (vec, 100);
	test_insert (vec, 100);
	test_erase (vec, 100);

	std::cout << std::endl;
	
	test_push (vec, 1000);
	test_pop (vec, 1000);
	test_insert (vec, 1000);
	test_erase (vec, 1000);
	
	std::cout << std::endl;

	test_push (vec, 10000);
	test_pop (vec, 10000);
	test_insert (vec, 10000);
	test_erase (vec, 10000);
	
	std::cout << std::endl;

	test_push (vec, 100000);
	test_pop (vec, 100000);
	test_insert (vec, 100000);
	test_erase (vec, 100000);
}
