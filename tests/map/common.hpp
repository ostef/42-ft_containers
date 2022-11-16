#ifndef FT_MAP_COMMON_HPP
#define FT_MAP_COMMON_HPP

#include "../common.hpp"

#define print_map(map) _print_map (map, #map)

template<typename T, typename Compare, typename Allocator>
void _print_map (const NS::map<T, Compare, Allocator> &map, const std::string &name)
{
	std::cout << "<" << name << ">\n" << std::endl;
	std::cout << "size = " << map.size () << std::endl;
	std::cout << "content is:" << std::endl;

	for (typename NS::map<T, Compare, Allocator>::const_iterator it = map.begin (); it != map.end (); it++)
		std::cout << "[" << it->first << "] " << it->second << std::endl;

	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
}

#ifdef TEST_STD

template<typename Key, typename T, typename Comp, typename Alloc>
bool ensure_balance_factor_correctness(const std::map<Key, T, Comp, Alloc> &map)
{
	(void)map;
	return true;
}

#else

template<typename Key, typename T, typename Comp, typename Alloc>
bool ensure_balance_factor_correctness(const ft::map<Key, T, Comp, Alloc> &map)
{
	return map.ensure_balance_factor_correctness ();
}

#endif

#endif
