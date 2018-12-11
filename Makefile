#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/03 01:08:13 by aalves            #+#    #+#              #
#    Updated: 2018/02/03 04:52:29 by aalves           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
FLAGS = -Werror -Wall -Wextra -Weverything -v -g
FTEST = -Werror -Wall -Wextra -Weverything -v
INCLUDES = -I./includes -I./libft/includes -pthread

LINK = libft_malloc.so

RM = rm -f

SRCS =	srcs/malloc.c \
	srcs/init.c \
	srcs/page.c \
	srcs/arena.c \
	srcs/tiny.c \
	srcs/small.c \
	srcs/large.c \
	srcs/free.c \
	srcs/cleaner.c \
	srcs/resize.c \
	srcs/realloc.c \
	srcs/debug.c


OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -fPIC $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling"
	@make -C ./libft
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -shared -o $(NAME) -L./libft -lft -fPIC
	@ln -sf libft_malloc_$(HOSTTYPE).so $(LINK)
	@echo "Done"

test: $(NAME)
	$(CC) $(FTEST) $(INCLUDES) srcs/main.c -o test -L. -lft_malloc -Wl,-rpath,.

try: test
	./test

clean:
	@echo "Cleaning"
	@make -C ./libft clean
	@$(RM) $(OBJS)
	@$(RM) $(LINK)
	@echo "Done"

fclean: clean
	@echo "Cleaning executable"
	@make -C ./libft fclean
	@$(RM) $(NAME)
	@echo "Done"

re: fclean all
