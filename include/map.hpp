/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:39:00 by soumanso          #+#    #+#             */
/*   Updated: 2022/07/20 17:39:00 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include <memory>
#include "rbt.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<pair<const Key, T> >
	>
	class map
	{
	public:
		typedef map<Key, T, Compare, Allocator> this_type;
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		//typedef ft::reverse_iterator<iterator> reverse_iterator;
		//typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

		public:
			bool operator() (const value_type &lhs, const value_type &rhs) const
			{
				return comp (lhs.first, rhs.first);
			}

		protected:
			value_compare (Compare c) : comp (c) {}

		protected:
			Compare comp;
		};

	public:
	private:

	};
}

#endif
