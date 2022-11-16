#ifndef FT_COMMON_HPP
#define FT_COMMON_HPP

#ifdef TEST_STD

#define NS std
#include <vector>
#include <map>
#include <stack>

#elif defined (TEST_FT)

# define NS ft
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

#else

#error "There should either be TEST_FT or TEST_STD defined."

#endif

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

#define print_expr(expr) std::cout << #expr " = " << (expr) << std::endl;

#endif
