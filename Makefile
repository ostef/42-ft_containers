SOURCE_FILES = tests.cpp
INCLUDE_DIR = include
INCLUDE_FILES = iterator.hpp type_traits.hpp utility.hpp vector.hpp map.hpp stack.hpp avl.hpp bst.hpp
CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -g3

all: ft.out std.out
	./ft.out > ft
	./std.out > std
	diff ft std

ft.out: $(SOURCE_FILES) $(addprefix $(INCLUDE_DIR)/,$(INCLUDE_FILES)) Makefile
	$(CPP) $(CPP_FLAGS) -I$(INCLUDE_DIR) $< -o $@ 

std.out: $(SOURCE_FILES) $(addprefix $(INCLUDE_DIR)/,$(INCLUDE_FILES)) Makefile
	$(CPP) $(CPP_FLAGS) -I$(INCLUDE_DIR) -DSTD_TEST $< -o $@ 

clean:

fclean:
	$(RM) ft.out
	$(RM) std.out

re: | fclean all

.PHONY: all clean fclean re
