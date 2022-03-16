/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:47:31 by soumanso          #+#    #+#             */
/*   Updated: 2022/03/16 16:19:28 by soumanso         ###   ########lyon.fr   */
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
	//#include <map.hpp>
	//#include <stack.hpp>
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
	EXPECT (ft::is_integral<ft::vector<int> >::value == false);
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
	EXPECT (ft::is_integral<const long>::value == true);
	EXPECT (ft::is_integral<const bool>::value == true);
	EXPECT (ft::is_integral<volatile bool>::value == true);
	EXPECT (ft::is_integral<const volatile bool>::value == true);
	EXPECT (ft::is_integral<volatile const bool>::value == true);
	EXPECT (ft::is_integral<int *>::value == false);
	EXPECT (ft::is_integral<void *>::value == false);
	EXPECT (ft::is_integral<int &>::value == false);
	EXPECT (ft::is_integral<const int &>::value == false);

	return ko;
}

int main ()
{
	int ko = 0;
	std::cout << "========= is_integral =========" << std::endl;
	ko += test_is_integral ();
	std::cout << "===============================" << std::endl;
	std::cout << ko << " KOs total." << std::endl;
}
