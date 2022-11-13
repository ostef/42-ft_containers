#include "common.hpp"

std::string rand_string (size_t len)
{
	static const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string result;
	result.reserve (len);

	for (size_t i = 0; i < len; i++)
	{
		result += chars[rand () % sizeof (chars)];
	}

	return result;
}

void test_insert (NS::map<std::string, int> &map, size_t n)
{
	benchmark bench ("insert");

	bench.start ();
	
	for (size_t i = 0; i < n; i += 1)
	{
		std::string key = rand_string (5);
		int value = rand ();
		
		map.insert (NS::make_pair (key, value));
	}

	bench.end (n);

	std::cout << bench << std::endl;
}

void test_find (NS::map<std::string, int> &map, size_t n)
{
	benchmark bench ("find");

	bench.start ();

	for (size_t i = 0; i < n; i += 1)
	{
		std::string key = rand_string (5);

		map.find (key);
	}

	bench.end (n);

	std::cout << bench << std::endl;
}

void test_erase (NS::map<std::string, int> &map)
{
	typedef NS::map<std::string, int>::iterator iterator;

	benchmark bench ("clear");

	size_t n = map.size ();
	bench.start ();

	iterator it = map.begin ();
	while (it != map.end ())
	{
		iterator next = it;
		++next;

		map.erase (it);

		it = next;
	}

	bench.end (n);

	std::cout << bench << std::endl;
}

int main ()
{
	NS::map<std::string, int> map;

	test_insert (map, 10);
	test_find (map, 10);
	test_erase (map);
	
	std::cout << std::endl;
	
	test_insert (map, 100);
	test_find (map, 100);
	test_erase (map);
	
	std::cout << std::endl;

	test_insert (map, 1000);
	test_find (map, 1000);
	test_erase (map);

	std::cout << std::endl;
	
	test_insert (map, 10000);
	test_find (map, 10000);
	test_erase (map);

	std::cout << std::endl;

	test_insert (map, 100000);
	test_find (map, 100000);
	test_erase (map);
}
