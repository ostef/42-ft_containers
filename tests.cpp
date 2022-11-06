/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:47:31 by soumanso          #+#    #+#             */
/*   Updated: 2022/03/03 14:47:31 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#ifdef STD_TEST
	#include <utility>
	#include <type_traits>
	#include <iterator>
	#include <vector>
	#include <map>
	#include <stack>
	namespace ft = std;
#else
	#include <utility.hpp>
	#include <type_traits.hpp>
	#include <iterator.hpp>
	#include <vector.hpp>
	#include <avl.hpp>
	#include <map.hpp>
	#include <stack.hpp>
#endif

#define EXPECT(cond)\
	if (!(cond))\
	{\
		ko += 1;\
		std::cout << "At line " << __LINE__ << ": Expected (" << #cond << "). KO." << std::endl;\
	}\
	else\
	{\
		std::cout << "At line " << __LINE__ << ": OK." << std::endl;\
	}

int test_is_integral ()
{
	int ko = 0;
	EXPECT (ft::is_integral<ft::vector<int>>::value == false);
	EXPECT (ft::is_integral<const char *>::value == false);
	EXPECT (ft::is_integral<char>::value == true);
	EXPECT (ft::is_integral<unsigned char>::value == true);
	EXPECT (ft::is_integral<short>::value == true);
	EXPECT (ft::is_integral<unsigned short>::value == true);
	EXPECT (ft::is_integral<int>::value == true);
	EXPECT (ft::is_integral<unsigned int>::value == true);
	EXPECT (ft::is_integral<long>::value == true);
	EXPECT (ft::is_integral<unsigned long>::value == true);
	EXPECT (ft::is_integral<long long>::value == true);
	EXPECT (ft::is_integral<unsigned long long>::value == true);
	EXPECT (ft::is_integral<const int>::value == true);
	EXPECT (ft::is_integral<int &>::value == false);
	EXPECT (ft::is_integral<const int &>::value == false);

	return ko;
}

#define PRINT(first, last)\
	std::cout << "At line " << __LINE__ << ": ";\
	print (first, last)

template<class TInput_Iterator>
void print(TInput_Iterator first, TInput_Iterator last)
{
	for (TInput_Iterator it = first; it != last; it++)
		std::cout << (*it) << "  ";
	std::cout << std::endl;
}

// This class is a wrapper around an int, that will print stuff when
// constructed/assigned/destructed.
class Elem
{
public:
	int value;

	Elem () : value (0) { std::cout << "Elem default constructed" << std::endl; }
	Elem (int value) : value (value) { std::cout << "Elem int constructed" << std::endl; }
	Elem (const Elem &other) { value = other.value; std::cout << "Elem copy constructed" << std::endl; }
	~Elem () { std::cout << "Elem destructed" << std::endl; }
	Elem &operator= (const Elem &other) { value = other.value; std::cout << "Elem assigned" << std::endl; return *this; }
};

std::ostream &operator<< (std::ostream &os, const Elem &x)
{
	os << x.value;
	return os;
}

int test_vector ()
{
	typedef int elem_type;
	//typedef Elem elem_type;	// Uncomment this if you want to print construction/assignment/destruction

	int ko = 0;

	ft::vector<elem_type> vec1 = ft::vector<elem_type> ();
	vec1.reserve (1000);
	for (int i = 0; i < 1000; i += 1)
		vec1.push_back (i);

	ft::vector<elem_type> vec = ft::vector<elem_type> ();
	
	vec.assign (vec1.begin () + 10, vec1.begin () + 100);
	PRINT (vec.begin (), vec.end ());
	
	vec.erase (vec.begin ());
	PRINT (vec.begin (), vec.end ());

	ft::vector<elem_type>::iterator it = vec.insert (vec.end (), 123);
	std::cout << (size_t)(it - vec.begin ()) << std::endl;
	PRINT (vec.begin (), vec.end ());

	vec.insert (vec.begin () + 3, 69105);
	PRINT (vec.begin (), vec.end ());

	vec.insert (vec.begin () + 3, 4, 42);
	PRINT (vec.begin (), vec.end ());

	vec.erase (vec.begin () + 10, vec.begin () + 15);
	PRINT (vec.begin (), vec.end ());
	
	vec.insert (vec.begin (), vec1.begin () + 100, vec1.end () - 100);
	PRINT (vec.begin (), vec.end ());

	vec.erase (vec.end () - 1);
	PRINT (vec.begin (), vec.end ());

	vec.swap (vec1);
	PRINT (vec.begin (), vec.end ());
	
	vec.swap (vec1);
	PRINT (vec.begin (), vec.end ());

	vec.push_back (10);
	vec.push_back (11);
	vec.push_back (12);
	vec.push_back (13);
	PRINT (vec.begin (), vec.end ());

	PRINT (vec.rbegin (), vec.rend ());

	return ko;
}

template<typename T>
bool ensure_sorted (const T &rbt)
{
	int prev = (int)0xffffffff;
	for (typename T::const_iterator it = rbt.begin (); it != rbt.end (); it++)
	{
		if (*it < prev)
			return false;
		prev = *it;
	}

	return true;
}

#ifndef STD_TEST
template<typename Tree>
bool ensure_no_loop_in_tree (const Tree &tree)
{
	typedef typename Tree::const_iterator It;
	typedef ft::vector<It> VecIt;

	VecIt visited_nodes;

	for (It it = tree.begin (); it != tree.end (); it++)
	{
		for (typename VecIt::iterator it2 = visited_nodes.begin (); it2 != visited_nodes.end (); it2++)
		{
			if (it == *it2)
				return false;
		}
		visited_nodes.push_back (it);
	}

	return true;
}
#endif

int test_avl_tree ()
{
	int ko = 0;

#ifndef STD_TEST

	ft::avl_tree<int> tree = ft::avl_tree<int> ();
	tree.insert (10);
	tree.insert (12);
	tree.insert (9);
	tree.insert (11);

	PRINT (tree.begin (), tree.end ());
	EXPECT (ensure_sorted (tree));

	{
		ft::avl_tree<int>::iterator it = tree.end ();
		--it;
		++it;
		EXPECT (it == tree.end ());
	}

	for (int i = 0; i < 1000; i += 1)
	{
		tree.insert (rand ());
		EXPECT (ensure_no_loop_in_tree (tree));
	}

	EXPECT (ensure_sorted (tree));

	for (int i = 0; i < 1000; i += 1)
	{
		ft::avl_tree<int>::iterator it = tree.find (rand ());
		if (it != tree.end ())
		{
			tree.erase (it);
		}

		EXPECT (ensure_no_loop_in_tree (tree));
	}
#endif

	return ko;
}

int main ()
{
	int ko = 0;
	std::cout << "========= is_integral =========" << std::endl;
	ko += test_is_integral ();
	std::cout << "========= vector =========" << std::endl;
	ko += test_vector ();
	std::cout << "========= avl_tree =========" << std::endl;
	ko += test_avl_tree ();
	std::cout << ko << " KOs total." << std::endl;

	return 0;
}
