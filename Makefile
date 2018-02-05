ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_NAME=malloc.c page.c block.c page_hlp.c free.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

INC = -Iinclude
CFLAGS = -Wall -Werror -Wextra $(INC) -g

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) --shared $(CFLAGS) $(OBJ)

obj/%.o: src/%.c
	@mkdir -p `dirname $@`
	gcc -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

fish:
	@echo 'setenv DYLD_LIBRARY_PATH /Users/briviere/projects/malloc'
	@echo 'setenv DYLD_INSERT_LIBRARIES libft_malloc_x86_64_Darwin.so'
	@echo 'setenv DYLD_FORCE_FLAT_NAMESPACE'
