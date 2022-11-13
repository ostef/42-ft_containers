/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:47:05 by soumanso          #+#    #+#             */
/*   Updated: 2022/11/13 14:57:21 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

#include <cstddef>

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

#define DECL_INTEGRAL(T)\
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

	DECL_INTEGRAL (bool);
	DECL_INTEGRAL (char);
	DECL_INTEGRAL (unsigned char);
	DECL_INTEGRAL (short);
	DECL_INTEGRAL (unsigned short);
	DECL_INTEGRAL (int);
	DECL_INTEGRAL (unsigned int);
	DECL_INTEGRAL (long);
	DECL_INTEGRAL (unsigned long);
	DECL_INTEGRAL (long long);
	DECL_INTEGRAL (unsigned long long);

	// These need special treatment, as they don't seem to be aliases for all of the above integer types...
	DECL_INTEGRAL (wchar_t);
	DECL_INTEGRAL (int8_t);

#undef DECL_INTEGRAL
}

#endif
