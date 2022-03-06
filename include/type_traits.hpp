/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfinae.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:43:15 by soumanso          #+#    #+#             */
/*   Updated: 2022/03/03 13:43:15 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SFINAE_HPP
#define FT_SFINAE_HPP

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class T, T v>
	struct integral_constant
	{
	public:
		typedef integral_constant<T, v> type;
		typedef T                       value_type;

	public:
		operator value_type () { return value; }

	public:
		static const value_type value = v;
	};

	template<class T>
	struct is_integral :
		public integral_constant<bool, false> {};

	template<class T>
	struct is_integral<bool> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<char> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<unsigned char> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<short> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<unsigned short> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<int> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<unsigned int> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<long> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<unsigned long> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<long long> :
		public integral_constant<bool, true> {};

	template<class T>
	struct is_integral<unsigned long long> :
		public integral_constant<bool, true> {};
}

#endif
