/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:39:25 by soumanso          #+#    #+#             */
/*   Updated: 2022/07/20 17:39:25 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "utility.hpp"
#include "vector.hpp"

namespace ft
{
	template<class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	protected:
		container_type c;

	public:
	
		explicit stack (const container_type &cont = container_type ()) : c (cont) {}
		stack (const stack &other) : c (other.cont) {}
		~stack () {}

		stack &operator= (const stack &other)
		{
			c = other.c;

			return *this;
		}

		reference top () { return c.back (); }
		const_reference top () const { return c.back (); }
		bool empty () const { return c.empty (); }
		size_type size () const { return c.size (); }
		
		void push (const value_type &val) { return c.push_back (val); }
		void pop () { c.pop_back (); }
	
		friend bool operator== (const stack &lhs, const stack &rhs)
		{
			return lhs.c == rhs.c;
		}

		friend bool operator!= (const stack &lhs, const stack &rhs)
		{
			return lhs.c != rhs.c;
		}
		
		friend bool operator< (const stack &lhs, const stack &rhs)
		{
			return lhs.c < rhs.c;
		}

		friend bool operator> (const stack &lhs, const stack &rhs)
		{
			return lhs.c > rhs.c;
		}

		friend bool operator<= (const stack &lhs, const stack &rhs)
		{
			return lhs.c <= rhs.c;
		}
		
		friend bool operator>= (const stack &lhs, const stack &rhs)
		{
			return lhs.c >= rhs.c;
		}
	};
};

#endif
