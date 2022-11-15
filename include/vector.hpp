/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:23:47 by soumanso          #+#    #+#             */
/*   Updated: 2022/11/15 13:56:16 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <stddef.h>
#include <limits>
#include "utility.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template<class T, class TAllocator = std::allocator<T> >
	class vector
	{
	public:
		typedef vector<T, TAllocator> this_type;
		typedef       T               value_type;
		typedef       T               &reference;
		typedef const T               &const_reference;
		typedef TAllocator            allocator_type;
		typedef size_t                size_type;
		typedef ptrdiff_t             difference_type;
		typedef       T               *iterator;
		typedef const T               *const_iterator;
		typedef ft::reverse_iterator<iterator>       reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	public:
		explicit vector (const allocator_type &alloc = allocator_type ());
		explicit vector (
			size_type n,
			const value_type &val = value_type (),
			const allocator_type &alloc = allocator_type ()
		);
		template<class TInput_Iterator>
		vector (
			TInput_Iterator first,
			TInput_Iterator last,
			const allocator_type &alloc = allocator_type (),
			typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled = 0
		);
		vector (const this_type &other);
		~vector ();

		// Copies all the elements from `other` into the container.
		// The container preserves its current allocator, which is used
		// to allocate storage in case of reallocation.
		this_type &operator= (const this_type &other);
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;

		template<class TInput_Iterator>
		void assign (
			TInput_Iterator first,
			TInput_Iterator last,
			typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled = 0
		);
		void assign (
			size_type n,
			const value_type &val
		);

		void swap (this_type &other);
		void reserve (size_type n);
		void resize (
			size_type n,
			value_type val = value_type ()
		);
		void clear ();
		void push_back (const value_type &val);
		void pop_back ();

		iterator insert (
			iterator position,
			const value_type &val
		);

		void insert (
			iterator position,
			size_type n,
			const value_type &val
		);

		template<class TInput_Iterator>
		void insert (
			iterator position,
			TInput_Iterator first,
			TInput_Iterator last,
			typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled = 0
		);

		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);

		reference at (size_type n);
		const_reference at (size_type n) const;
		reference back ();
		const_reference back () const;
		reference front ();
		const_reference front () const;
	
		iterator begin ();
		const_iterator begin () const;
		iterator end ();
		const_iterator end () const;
		
		reverse_iterator rbegin ();
		const_reverse_iterator rbegin () const;
		reverse_iterator rend ();
		const_reverse_iterator rend () const;

		bool empty () const;
		value_type *data ();
		const value_type *data () const;
		size_type capacity () const;
		size_type size () const;
		size_type max_size () const;
		allocator_type get_allocator () const;

	private:
		value_type *_data;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;
	};

// Constructors, destructor

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (const allocator_type &alloc) :
		_data (NULL),
		_size (0),
		_capacity (0),
		_alloc (alloc)
	{}

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (
		size_type n,
		const value_type &val,
		const allocator_type &alloc
	) :
		_data (NULL),
		_size (0),
		_capacity (0),
		_alloc (alloc)
	{
		assign (n, val);
	}

	template<class T, class TAllocator>
	template<class TInput_Iterator>
	vector<T, TAllocator>::vector (
		TInput_Iterator first,
		TInput_Iterator last,
		const allocator_type &alloc,
		typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled
	) :
		_data (NULL),
		_size (0),
		_capacity (0),
		_alloc (alloc)
	{
		(void)enabled;

		assign (first, last);
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (const this_type &other) :
		_data (NULL),
		_size (0),
		_capacity (0),
		_alloc (other._alloc)
	{
		assign (other.begin (), other.end ());
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::~vector ()
	{
		for (size_t i = 0; i < _size; i += 1)
			_alloc.destroy (_data + i);

		_alloc.deallocate (_data, _capacity);
		_data = NULL;
		_size = 0;
		_capacity = 0;
	}

// Operators

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::this_type &vector<T, TAllocator>::operator= (const this_type &other)
	{
		assign (other.begin (), other.end ());

		return *this;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::operator[] (size_type n)
	{
		return _data[n];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::operator[] (size_type n) const
	{
		return _data[n];
	}

// Actual functionality

	template<class T, class TAllocator>
	template<class TInput_Iterator>
	void vector<T, TAllocator>::assign (
		TInput_Iterator first,
		TInput_Iterator last,
		typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled
	)
	{
		(void)enabled;

		clear ();
		for (TInput_Iterator it = first; it != last; ++it)
			push_back (*it);
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::assign (
		vector<T, TAllocator>::size_type n,
		const vector<T, TAllocator>::value_type &val
	)
	{
		clear ();
		for (size_type i = 0; i < n; i += 1)
			push_back (val);
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::swap (vector<T, TAllocator> &other)
	{
		value_type     *tmp_data     = _data;
		size_type      tmp_size     = _size;
		size_type      tmp_capacity = _capacity;
		allocator_type tmp_alloc    = _alloc;

		_data     = other._data;
		_size     = other._size;
		_capacity = other._capacity;
		_alloc    = other._alloc;

		other._data     = tmp_data;
		other._size     = tmp_size;
		other._capacity = tmp_capacity;
		other._alloc    = tmp_alloc;
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::reserve (vector<T, TAllocator>::size_type n)
	{
		if (n <= _capacity)
			return;

		value_type *new_data = _alloc.allocate (n);
		for (size_type i = 0; i < _size; i += 1)
		{
			_alloc.construct (new_data + i, _data[i]);
			_alloc.destroy (_data + i);
		}
		_alloc.deallocate (_data, _capacity);
		_capacity = n;
		_data = new_data;
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::resize (vector<T, TAllocator>::size_type n, vector<T, TAllocator>::value_type val)
	{
		while (_size > n)
			pop_back ();
		while (_size < n)
			push_back (val);
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::clear ()
	{
		while (_size > 0)
			pop_back ();
	}
	
	template<class T, class TAllocator>
	void vector<T, TAllocator>::push_back (const vector<T, TAllocator>::value_type &val)
	{
		if (_size >= _capacity)
			reserve (_capacity * 2 + 8);
		_alloc.construct (end (), val);
		_size += 1;
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::pop_back ()
	{
		if (_size == 0)
			throw std::runtime_error ("vector is empty");

		_alloc.destroy (end () - 1);
		_size -= 1;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::insert (vector<T, TAllocator>::iterator position, const vector<T, TAllocator>::value_type &val)
	{
		size_type index = position - begin ();
		insert (position, 1, val);

		return begin () + index;
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::insert (vector<T, TAllocator>::iterator position, vector<T, TAllocator>::size_type n, const vector<T, TAllocator>::value_type &val)
	{
		if (n == 0)
			return;

		size_type index = position - begin ();
		
		if (_size + n > _capacity)
			reserve (_capacity * 2 + n);
		
		position = begin () + index;

		for (iterator it = end () + n - 1; it != position + n - 1; it--)
			*it = *(it - n);

		_size += n;

		for (iterator it = position; it != position + n; it++)
			*it = val;
	}

	template<class T, class TAllocator>
	template<class TInput_Iterator>
	void vector<T, TAllocator>::insert (typename vector<T, TAllocator>::iterator position, TInput_Iterator first, TInput_Iterator last, typename enable_if<!is_integral<TInput_Iterator>::value>::type *enabled)
	{
		(void)enabled;
	
		size_type index = position - begin ();
		size_type n = std::distance (first, last);
		
		if (n == 0)
			return;
		
		if (_size + n > _capacity)
			reserve (_capacity * 2 + n);

		position = begin () + index;

		for (iterator it = end () + n - 1; it != position + n - 1; it--)
			*it = *(it - n);

		_size += n;

		size_type i = index;
		for (TInput_Iterator it = first; it != last; it++)
		{
			_data[i] = *it;
			i += 1;
		}
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::erase (vector<T, TAllocator>::iterator position)
	{
		return erase (position, position + 1);
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::erase (vector<T, TAllocator>::iterator first, vector<T, TAllocator>::iterator last)
	{
		// "If [first, last) is an empty range, then last is returned"
		if (last <= first)
			return last;

		size_type first_index = first - begin ();
		size_type n = last - first;

		for (size_type i = first_index; i + n < _size; i += 1)
			_data[i] = _data[i + n];

		for (size_type i = 0; i < n; i += 1)
			pop_back ();

		return last - n;
	}

// Getters and setters, one-liners

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::at (vector<T, TAllocator>::size_type n)
	{
		if (n >= _size)
			throw std::out_of_range ("Bounds check failure in vector.");
		return _data[n];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::at (vector<T, TAllocator>::size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range ("Bounds check failure in vector.");
		return _data[n];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::back ()
	{
		if (_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return _data[_size - 1];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::back () const
	{
		if (_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return _data[_size - 1];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::front ()
	{
		if (_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return _data[0];
	}
	
	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::front () const
	{
		if (_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return _data[0];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::begin ()
	{
		return _data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_iterator vector<T, TAllocator>::begin () const
	{
		return _data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::end ()
	{
		return _data + _size;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_iterator vector<T, TAllocator>::end () const
	{
		return _data + _size;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reverse_iterator vector<T, TAllocator>::rbegin ()
	{
		return reverse_iterator (end ());
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reverse_iterator vector<T, TAllocator>::rbegin () const
	{
		return const_reverse_iterator (end ());
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reverse_iterator vector<T, TAllocator>::rend ()
	{
		return reverse_iterator (begin ());
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reverse_iterator vector<T, TAllocator>::rend () const
	{
		return const_reverse_iterator (begin ());
	}

	template<class T, class TAllocator>
	bool vector<T, TAllocator>::empty () const
	{
		return _size == 0;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::value_type *vector<T, TAllocator>::data ()
	{
		return _data;
	}

	template<class T, class TAllocator>
	const typename vector<T, TAllocator>::value_type *vector<T, TAllocator>::data () const
	{
		return _data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::capacity () const
	{
		return _capacity;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::size () const
	{
		return _size;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::max_size () const
	{
		return std::numeric_limits<size_type>::max ();
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::allocator_type vector<T, TAllocator>::get_allocator () const
	{
		return _alloc;
	}

	// Relational operators

	template<class T, class TAllocator>
	bool operator== (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		if (lhs.size () != rhs.size ())
			return false;

		return ft::equal (lhs.begin (), lhs.end (), rhs.begin ());
	}

	template<class T, class TAllocator>
	bool operator!= (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class TAllocator>
	bool operator< (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		return ft::lexicographical_compare (lhs.begin (), lhs.end (), rhs.begin (), rhs.end ());
	}

	template<class T, class TAllocator>
	bool operator> (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		return ft::lexicographical_compare (rhs.begin (), rhs.end (), lhs.begin (), lhs.end ());
	}

	template<class T, class TAllocator>
	bool operator<= (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template<class T, class TAllocator>
	bool operator>= (const vector<T, TAllocator> &lhs, const vector<T, TAllocator> &rhs)
	{
		return lhs > rhs || lhs == rhs;
	}
}

namespace std
{
	template<class T, class Alloc>
	void swap (ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
	{
		lhs.swap (rhs);
	}
}

#endif
