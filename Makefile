ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_NAME=malloc.c page.c block.c page_hlp.c free.c mutex.c realloc.c\
		 show.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

INC = -Iinclude
CFLAGS = -Wall -Wextra $(INC) -g
ifneq ($(shell uname), Linux)
	CFLAGS += -Werror
endif

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

ifeq ($(shell uname), Linux)
lldb_init:
	@echo 'env LD_PRELOAD=$(shell pwd)/$(NAME)' > .lldbinit
else
lldb_init:
	@echo 'env DYLD_LIBRARY_PATH=/Users/briviere/projects/malloc' > .lldbinit
	@echo 'env DYLD_INSERT_LIBRARIES=libft_malloc_x86_64_Darwin.so' >> .lldbinit
	@echo 'env DYLD_FORCE_FLAT_NAMESPACE=1' >> .lldbinit
endif

lldb: all lldb_init
	@gcc -o test test.c $(CFLAGS)
	@lldb ./test
	@rm -f test

ls: all lldb_init
	@lldb ls

test: all
	gcc test.c -Iinclude -g -O0 -L. -lft_malloc_$(HOSTTYPE)
	@LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH) ./a.out

fish:
	@echo 'setenv DYLD_LIBRARY_PATH /Users/briviere/projects/malloc; setenv DYLD_INSERT_LIBRARIES libft_malloc_x86_64_Darwin.so; setenv DYLD_FORCE_FLAT_NAMESPACE 1'

