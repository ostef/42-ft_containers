/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:08:55 by soumanso          #+#    #+#             */
/*   Updated: 2022/10/21 23:55:42 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

namespace ft
{
/*
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
*/

	template<class TIter>
	struct iterator_traits
	{
		typedef typename TIter::difference_type   difference_type;
		typedef typename TIter::value_type        value_type;
		typedef typename TIter::pointer           pointer;
		typedef typename TIter::reference         reference;
		typedef typename TIter::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t                  difference_type;
		typedef T                               value_type;
		typedef T                               *pointer;
		typedef T                               &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t                  difference_type;
		typedef       T                         value_type;
		typedef const T                         *pointer;
		typedef const T                         &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<
		class TCategory,
		class T,
		class TDistance = std::ptrdiff_t,
		class TPointer = T *,
		class TReference = T &
	>
	struct iterator
	{
		typedef TCategory  iterator_category;
		typedef T          value_type;
		typedef TDistance  difference_type;
		typedef TPointer   pointer;
		typedef TReference reference;
	};

	template<class TIter>
	class reverse_iterator
	{
	public:
		typedef          TIter                                     iterator_type;
		typedef typename iterator_traits<TIter>::difference_type   difference_type;
		typedef typename iterator_traits<TIter>::iterator_category iterator_category;
		typedef typename iterator_traits<TIter>::value_type        value_type;
		typedef typename iterator_traits<TIter>::pointer           pointer;
		typedef typename iterator_traits<TIter>::reference         reference;

	public:
		reverse_iterator ()
			: _base () {}
		explicit reverse_iterator (iterator_type it)
			: _base (it) {}
		template<class TOther_Iter>
		reverse_iterator (const reverse_iterator<TOther_Iter> &other)
			: _base (other.base ()) {}

		template<class TOther_Iter>
		reverse_iterator &operator= (const reverse_iterator<TOther_Iter> &other)
		{
			_base = other.base ();
			return *this;
		}

		iterator_type base () const { return _base; }

		reference operator* () const
		{
			iterator_type it = _base;
			// @Speed: operator-- might be slow, like in rbt. We should cache its result
			return *(--it);
		}
		
		pointer operator-> () const
		{
			iterator_type it = _base;
			return (--it).operator-> ();
		}

		reference operator[] (difference_type n) const
		{
			return _base[-n - 1];
		}

		reverse_iterator operator+ (difference_type n) const
		{
			return reverse_iterator (_base - n);
		}
		
		reverse_iterator &operator++ ()
		{
			--_base;
			return *this;
		}
		
		reverse_iterator operator++ (int)
		{
			reverse_iterator tmp = *this;
			--_base;
			return tmp;
		}
		
		reverse_iterator &operator+= (difference_type n)
		{
			_base -= n;
			return *this;
		}

		reverse_iterator operator- (difference_type n) const
		{
			return reverse_iterator (_base + n);
		}

		reverse_iterator &operator-- ()
		{
			++_base;
			return *this;
		}

		reverse_iterator operator-- (int)
		{
			reverse_iterator tmp = *this;
			++_base;
			return tmp;
		}

		reverse_iterator &operator-= (difference_type n)
		{
			_base += n;
			return *this;
		}

	private:
		iterator_type _base;
	};

	template<class TIter_L, class TIter_R>
	bool operator== (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () == right.base ();
	}

	template<class TIter_L, class TIter_R>
	bool operator!= (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () != right.base ();
	}

	template<class TIter_L, class TIter_R>
	bool operator< (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () > right.base ();
	}

	template<class TIter_L, class TIter_R>
	bool operator<= (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () >= right.base ();
	}

	template<class TIter_L, class TIter_R>
	bool operator> (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () < right.base ();
	}

	template<class TIter_L, class TIter_R>
	bool operator>= (const reverse_iterator<TIter_L> &left, const reverse_iterator<TIter_R> &right)
	{
		return left.base () <= right.base ();
	}

	template<class TIter>
	reverse_iterator<TIter> operator+ (
		typename reverse_iterator<TIter>::difference_type n,
		const reverse_iterator<TIter> &it
	)
	{
		return it + n;
	}

	template<class TIter>
	typename reverse_iterator<TIter>::difference_type operator- (
		const reverse_iterator<TIter> &left,
		const reverse_iterator<TIter> &right
	)
	{
		return left.base () - right.base ();
	}
}

#endif
