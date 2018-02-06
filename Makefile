ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_NAME=malloc.c page.c block.c page_hlp.c free.c mutex.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

INC = -Iinclude
CFLAGS = -Wall -Werror -Wextra -O0 $(INC) -g
LIB=-L. -lft_malloc_$(HOSTTYPE)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) --shared -fPIC $(CFLAGS) $(OBJ) -Llibft -lft -Ilibft/include

obj/%.o: src/%.c
	@mkdir -p `dirname $@`
	gcc -c -o $@ $(CFLAGS) $< -Ilibft/include

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@gcc -o test test.c $(CFLAGS) $(LIB)
	@./test
	@rm -f test

lldb: all
	@gcc -o test test.c $(CFLAGS) $(LIB)
	@lldb ./test
	@rm -f test

fish:
	@echo 'setenv DYLD_LIBRARY_PATH /Users/briviere/projects/malloc; setenv DYLD_INSERT_LIBRARIES libft_malloc_x86_64_Darwin.so; setenv DYLD_FORCE_FLAT_NAMESPACE 1'

lldb_env:
	@echo 'env DYLD_LIBRARY_PATH=/Users/briviere/projects/malloc'
	@echo 'env DYLD_INSERT_LIBRARIES=libft_malloc_x86_64_Darwin.so'
	@echo 'env DYLD_FORCE_FLAT_NAMESPACE=1'
