#include "common.hpp"

template<class T>
void iter(T &cont)
{
	for (typename T::iterator it = cont.begin (); it != cont.end (); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

template<class T>
void const_iter(const T &cont)
{
	for (typename T::const_iterator it = cont.begin (); it != cont.end (); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

template<class T>
void riter(T &cont)
{
	for (typename T::reverse_iterator it = cont.rbegin (); it != cont.rend (); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

template<class T>
void const_riter(const T &cont)
{
	for (typename T::const_reverse_iterator it = cont.rbegin (); it != cont.rend (); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
}

int main()
{
	NS::vector<int> vec1;
	for (int i = 0; i < 5; i++)
		vec1.push_back (i);

	iter (vec1);
	const_iter (vec1);
	riter (vec1);
	const_riter (vec1);
}
