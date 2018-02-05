ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_NAME=malloc.c page.c zone.c
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

help:
	@echo 'run the following command to replace system malloc:'
	@echo 'export DYLD_LIBRARY_PATH=$(shell pwd)'
	@echo 'export DYLD_INSERT_LIBRARIES=$(NAME)'
	@echo 'export DYLD_FORCE_FLAT_NAMESPACE'
