NAME = tests
SRC_FILES = tests.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
INCLUDE_DIRS = include
DEPENDENCIES = include/iterator.hpp include/type_traits.hpp include/utility.hpp include/vector.hpp
CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98 $(addprefix -I,$(INCLUDE_DIRS))

all: stdtests fttests

stdtests: $(SRC_FILES) $(DEPENDENCIES)
	$(CPP) $(CPP_FLAGS) -DSTD_TEST $< -o $@

fttests: $(SRC_FILES) $(DEPENDENCIES)
	$(CPP) $(CPP_FLAGS) $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
