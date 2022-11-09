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
#include "avl.hpp"
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
		typedef Allocator allocator_type;
		typedef Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		class value_compare
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			friend class map;

		public:
			value_compare (Compare c) : comp (c) {}

			bool operator() (const value_type &lhs, const value_type &rhs) const
			{
				return comp (lhs.first, rhs.first);
			}

		protected:
			Compare comp;
		};

		typedef typename allocator_type::template rebind<avl_node<value_type > >::other node_allocator;
		typedef avl_tree<value_type, value_compare, node_allocator> tree;

		typedef typename tree::iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::reverse_iterator reverse_iterator;
		typedef typename tree::const_reverse_iterator const_reverse_iterator;

		typedef typename tree::size_type size_type;
		typedef ptrdiff_t difference_type;

	private:

		class key_value_compare
		{
		public:
			typedef bool result_type;
			typedef key_type first_argument_type;
			typedef value_type second_argument_type;

		public:
			key_value_compare (Compare c) : comp (c) {}

			bool operator() (const key_type &lhs, const value_type &rhs) const
			{
				return comp (lhs, rhs.first);
			}

			bool operator() (const value_type &lhs, const key_type &rhs) const
			{
				return comp (lhs.first, rhs);
			}

		protected:
			Compare comp;
		};

	private:
		tree _tree;

	public:
		map () : _tree (value_compare (Compare ()), allocator_type ()) {}

		explicit map (const Compare &comp, const allocator_type &alloc = allocator_type ()) :
			_tree (value_compare (comp), alloc) {}
		
		template<typename InputIt>
		map (InputIt first, InputIt last, const Compare &comp = Compare (), const allocator_type &alloc = allocator_type ()) :
			_tree (first, last, value_compare (comp), alloc) {}

		map (const map &other) : _tree (other._tree) {}

		~map () {}

		map &operator= (const map &other)
		{
			_tree = other._tree;

			return *this;
		}

		pair<iterator, bool> insert (const value_type &value)
		{
			return _tree.insert (value);
		}

		iterator insert (iterator pos, const value_type &value)
		{
			(void)pos;	// I am not sure what this is for

			return insert (value).first;
		}

		template<typename InputIt>
		void insert (InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; it++)
				insert (*it);
		}

		iterator erase (iterator pos)
		{
			return _tree.erase (pos);
		}

		iterator erase (iterator first, iterator last)
		{
			return _tree.erase (first, last);
		}

		size_type erase (const Key &key)
		{
			iterator it = find (key);
			if (it == end ())
				return 0;
			
			_tree.erase (it);

			return 1;
		}

		void clear ()
		{
			_tree.clear ();
		}

		void swap (map &other)
		{
			_tree.swap (other._tree);
		}

		size_type count (const Key &key) const
		{
			const_iterator it = find (key);
			if (it == _tree.end ())
				return 0;

			return 1;
		}

		iterator find (const Key &key)
		{
			return _tree.find (key, key_value_compare (_tree.value_comp ().comp));
		}

		const_iterator find (const Key &key) const
		{
			return _tree.find (key, key_value_compare (_tree.value_comp ().comp));
		}

		pair<iterator, iterator> equal_range (const Key &key)
		{
			iterator lower = find (key);
			bool found_lower_bound = lower != end ();
			
			if (!found_lower_bound)
			{
				for (lower = begin (); lower != end (); lower++)
				{
					if (_tree.value_comp ().comp (key, lower->first))
						break;
				}
			}

			if (found_lower_bound)
			{
				iterator upper = lower;

				return ft::make_pair (lower, ++upper);
			}

			return ft::make_pair (lower, lower);
		}
		
		pair<const_iterator, const_iterator> equal_range (const Key &key) const
		{
			const_iterator lower = find (key);
			bool found_lower_bound = lower != end ();
			
			if (!found_lower_bound)
			{
				for (lower = begin (); lower != end (); lower++)
				{
					if (_tree.value_comp ().comp (key, lower->first))
						break;
				}
			}

			if (found_lower_bound)
			{
				const_iterator upper = lower;

				return ft::make_pair (lower, ++upper);
			}

			return ft::make_pair (lower, lower);
		}

		iterator lower_bound (const Key &key) { return equal_range (key).first; }
		const_iterator lower_bound (const Key &key) const { return equal_range (key).first; }

		iterator upper_bound (const Key &key) { return equal_range (key).second; }
		const_iterator upper_bound (const Key &key) const { return equal_range (key).second; }

		T &at (const Key &key)
		{
			typename tree::iterator it = _tree.find (key, key_value_compare (_tree.value_comp ().comp));
			if (it == _tree.end ())
				throw std::out_of_range ("key was not found in the map");
		
			return it->second;
		}

		const T &at (const Key &key) const
		{
			const_iterator it = _tree.find (key, key_value_compare (_tree.value_comp ().comp));
			if (it == _tree.end ())
				throw std::out_of_range ("key was not found in the map");
		
			return it->second;
		}

		T &operator[] (const Key &key)
		{
			iterator it = find (key);
			if (it == _tree.end ())
				it = _tree.insert (ft::make_pair (key, mapped_type ())).first;
			
			ASSERT (it->first == key && "Keys don't match");

			return it->second;
		}

		bool empty () const { return _tree.empty (); }
		size_type size () const { return _tree.size (); }
		size_type max_size () const { return _tree.max_size (); }
		allocator_type get_allocator () const { return _tree.get_allocator (); }
		value_compare value_comp () const { return _tree.value_comp (); }
		key_compare key_comp () const { return _tree.value_comp ().comp; }

		iterator begin () { return _tree.begin (); }
		const_iterator begin () const { return _tree.begin (); }

		iterator end () { return _tree.end (); }
		const_iterator end () const { return _tree.end (); }

		reverse_iterator rbegin () { return _tree.rbegin (); }
		const_reverse_iterator rbegin () const { return _tree.rbegin (); }

		reverse_iterator rend () { return _tree.rend (); }
		const_reverse_iterator rend () const { return _tree.rend (); }

		friend bool operator== (const map &lhs, const map &rhs)
		{
			return lhs._tree == rhs._tree;
		}

		friend bool operator!= (const map &lhs, const map &rhs)
		{
			return lhs._tree != rhs._tree;
		}

		friend bool operator< (const map &lhs, const map &rhs)
		{
			return lhs._tree < rhs._tree;
		}

		friend bool operator> (const map &lhs, const map &rhs)
		{
			return lhs._tree > rhs._tree;
		}

		friend bool operator<= (const map &lhs, const map &rhs)
		{
			return lhs._tree <= rhs._tree;
		}

		friend bool operator>= (const map &lhs, const map &rhs)
		{
			return lhs._tree >= rhs._tree;;
		}
	};
}

#endif
