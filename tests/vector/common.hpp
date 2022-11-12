#ifndef FT_VECTOR_COMMON_HPP
#define FT_VECTOR_COMMON_HPP

#include "../common.hpp"

#define print_vector(vec) _print_vector (vec, #vec)

template<typename T, typename Allocator>
void _print_vector (const NS::vector<T, Allocator> &vec, const std::string &name)
{
	std::cout << "<" << name << ">\n" << std::endl;
	std::cout << "size = " << vec.size () << std::endl;
	std::cout << "content is:" << std::endl;

	size_t i = 0;
	for (typename NS::vector<T, Allocator>::const_iterator it = vec.begin (); it != vec.end (); it++, i += 1)
		std::cout << "[" << i << "] " << *it << std::endl;

	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
}

#endif
