/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:23:47 by soumanso          #+#    #+#             */
/*   Updated: 2022/01/16 20:23:47 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <stdexcept>
#include <stddef.h>
#include <limits>
#include "iterator.hpp"

namespace ft
{
	template<class T, class TAllocator = std::allocator<T>>
	class vector
	{
	public:
		typedef       T               value_type;
		typedef       T               &reference;
		typedef const T               &const_reference;
		typedef TAllocator            allocator_type;
		typedef size_t                size_type;
		typedef       T               *iterator;
		typedef const T               *const_iterator;
		typedef reverse_iterator<iterator>       reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

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
			const allocator_type &alloc = allocator_type ()
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
			TInput_Iterator last
		);
		void assign (
			size_type n,
			const value_type &val
		);

		void swap (this_type &other);
		// @Todo
		void reserve (size_type n);
		// @Todo
		void resize (
			size_type n,
			value_type val = value_type ()
		);
		// @Todo
		void clear ();
		// @Todo
		void push_back (const value_type &val);
		// @Todo
		void pop_back ();
		// @Todo
		iterator insert (
			iterator position,
			const value_type &val
		);
		// @Todo
		void insert (
			iterator position,
			size_type n,
			const value_type &val
		);
		// @Todo
		template<class TInput_Iterator>
		void insert (
			iterator position,
			TInput_Iterator first,
			TInput_Iterator last
		);
		// @Todo
		iterator erase (iterator position);
		// @Todo
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
		value_type *data () noexcept;
		const value_type *data () const noexcept;
		size_type capacity () const;
		size_type size () const;
		size_type max_size () const;
		allocator_type get_allocator () const;

	private:
		value_type *m_data;
		size_type m_size;
		size_type m_capacity;
		allocator_type m_alloc;
	};

// Constructors, destructor

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (const allocator_type &alloc) :
		m_data (NULL),
		m_size (0),
		m_capacity (0),
		m_alloc (alloc)
	{}

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (
		size_type n,
		const value_type &val,
		const allocator_type &alloc
	) :
		m_data (NULL),
		m_size (0),
		m_capacity (0),
		m_alloc (alloc)
	{
		insert (begin (), n, val);
	}

	template<class T, class TAllocator>
	template<class TInput_Iterator>
	vector<T, TAllocator>::vector (
		TInput_Iterator first,
		TInput_Iterator last,
		const allocator_type &alloc
	) :
		m_data (NULL),
		m_size (0),
		m_capacity (0),
		m_alloc (alloc)
	{
		insert (begin (), first, last);
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::vector (const this_type &other)
	{
		m_alloc = other.get_allocator ();
		m_data = m_alloc.allocate (sizeof (value_type) * other.capacity ());
		m_capacity = other.capacity ();
		m_size = 0;
		assign (other.begin (), other.end ());
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::~vector ()
	{
		m_alloc.deallocate (m_data, sizeof (value_type) * m_capacity);
		m_data = NULL;
		m_size = 0;
		m_capacity = 0;
	}

// Operators

	template<class T, class TAllocator>
	vector<T, TAllocator>::this_type &vector<T, TAllocator>::operator= (const this_type &other)
	{
		assign (other.begin (), other.end ());
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::reference vector<T, TAllocator>::operator[] (size_type n)
	{
		return at (n);
	}

	template<class T, class TAllocator>
	vector<T, TAllocator>::const_reference vector<T, TAllocator>::operator[] (size_type n) const
	{
		return at (n);
	}

// Actual functionality

	template<class T, class TAllocator>
	template<class TInput_Iterator>
	void vector<T, TAllocator>::assign (TInput_Iterator first, TInput_Iterator last)
	{
		clear ();
		for (TInput_Iterator it = first; it != last; ++it)
			push_back (*it);
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::assign (size_type n, const value_type &val)
	{
		clear ();
		for (size_type i = 0; i < n; i += 1)
			push_back (val);
	}

	template<class T, class TAllocator>
	void vector<T, TAllocator>::swap (vector<T, TAllocator> &other)
	{
		value_type     *tmp_data     = m_data;
		size_type      tmp_size     = m_size;
		size_type      tmp_capacity = m_capacity;
		allocator_type tmp_alloc    = m_alloc;

		m_data     = other.m_data;
		m_size     = other.m_size;
		m_capacity = other.m_capacity;
		m_alloc    = other.m_alloc;

		other.m_data     = tmp_data;
		other.m_size     = tmp_size;
		other.m_capacity = tmp_capacity;
		other.m_alloc    = tmp_alloc;
	}

// Getters and setters, one-liners

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::at (size_type n)
	{
		if (n >= m_size)
			throw std::out_of_range ("Bounds check failure in vector.");
		return m_data[n];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::at (size_type n) const
	{
		if (n >= m_size)
			throw std::out_of_range ("Bounds check failure in vector.");
		return m_data[n];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::back ()
	{
		if (m_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return m_data[m_size - 1];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::back () const
	{
		if (m_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return m_data[m_size - 1];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::reference vector<T, TAllocator>::front ()
	{
		if (m_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return m_data[0];
	}
	
	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_reference vector<T, TAllocator>::front () const
	{
		if (m_size == 0)
			throw std::out_of_range ("Vector is empty.");
		return m_data[0];
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::begin ()
	{
		return m_data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_iterator vector<T, TAllocator>::begin () const
	{
		return m_data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::iterator vector<T, TAllocator>::end ()
	{
		return m_data + m_size;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::const_iterator vector<T, TAllocator>::end () const
	{
		return m_data + m_size;
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
		return m_size == 0;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::value_type *vector<T, TAllocator>::data () noexcept
	{
		return m_data;
	}

	template<class T, class TAllocator>
	typename const vector<T, TAllocator>::value_type *vector<T, TAllocator>::data () const noexcept;
	{
		return m_data;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::capacity () const
	{
		return m_capacity;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::size () const
	{
		return m_size;
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::size_type vector<T, TAllocator>::max_size () const
	{
		return std::numeric_limits<size_type>::max ();
	}

	template<class T, class TAllocator>
	typename vector<T, TAllocator>::allocator_type vector<T, TAllocator>::get_allocator () const
	{
		return m_alloc;
	}
}

#endif
