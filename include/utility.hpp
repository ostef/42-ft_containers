/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:27:47 by soumanso          #+#    #+#             */
/*   Updated: 2022/03/03 14:27:47 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

	public:
		pair ()
			: first (), second () {}
		pair (const first_type &x, const second_type &y)
			: first (x), second (y) {}
		pair (const pair &other)
			: first (other.first), second (other.second) {}
		template<class T1_Other, class T2_Other>
		pair (const pair<T1_Other, T2_Other> &other)
			: first (other.first), second (other.second) {}
		
		pair &operator= (const pair &other)
		{
			first = other.first;
			second = other.second;

			return *this;
		}

	public:
		first_type first;
		second_type second;
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair (T1 first, T2 second)
	{
		return pair<T1, T2> (first, second);
	}

	template<class T1, class T2>
	bool operator== (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		return left.first == right.first && left.second == right.second;
	}

	template<class T1, class T2>
	bool operator!= (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		return !(left == right);
	}

	template<class T1, class T2>
	bool operator< (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		if (left.first < right.first)
			return true;
		else if (left.first > right.first)
			return false;
		if (left.second < right.second)
			return true;
		else if (left.second > right.second)
			return false;
		return false;
	}

	template<class T1, class T2>
	bool operator<= (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		return !(right < left);
	}

	template<class T1, class T2>
	bool operator> (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		return right < left;
	}

	template<class T1, class T2>
	bool operator>= (const pair<T1, T2> &left, const pair<T1, T2> &right)
	{
		return right <= left;
	}
}

#endif
