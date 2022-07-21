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
	
	vec.insert (vec.begin () + 3, 69105);
	PRINT (vec.begin (), vec.end ());

	vec.insert (vec.begin () + 3, 4, 0xb00b);
	PRINT (vec.begin (), vec.end ());

	vec.erase (vec.begin () + 10, vec.begin () + 15);
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

int main ()
{
	int ko = 0;
	std::cout << "========= is_integral =========" << std::endl;
	ko += test_is_integral ();
	std::cout << "========= vector =========" << std::endl;
	ko += test_vector ();
	std::cout << ko << " KOs total." << std::endl;

	return ko;
}
