/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:47:05 by soumanso          #+#    #+#             */
/*   Updated: 2022/07/21 14:47:05 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

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

#define IS_INTEGRAL(T)\
	template<>\
	struct is_integral<T> :\
		public integral_constant<bool, true> {};\
	template<>\
	struct is_integral<const T> :\
		public integral_constant<bool, true> {};\
	template<>\
	struct is_integral<volatile T> :\
		public integral_constant<bool, true> {};\
	template<>\
	struct is_integral<const volatile T> :\
		public integral_constant<bool, true> {}

	IS_INTEGRAL (bool);
	IS_INTEGRAL (char);
	IS_INTEGRAL (unsigned char);
	IS_INTEGRAL (short);
	IS_INTEGRAL (unsigned short);
	IS_INTEGRAL (int);
	IS_INTEGRAL (unsigned int);
	IS_INTEGRAL (long);
	IS_INTEGRAL (unsigned long);
	IS_INTEGRAL (long long);
	IS_INTEGRAL (unsigned long long);

#undef IS_INTEGRAL
}

#endif
