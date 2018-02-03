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

NAME = libft_malloc_$HOSTTYPE.so
CC = clang
FLAGS = -Werror -Wall -Wextra 
INCLUDES = -I./includes -I./libft/includes

RM = rm -f

SRCS =	srcs/malloc.c


OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling"
	@make -C ./libft
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) libft/libft.a -shared -o $(NAME) 
	@echo "Done"

test: $(NAME)

	$(CC) $(FLAGS) $(INCLUDES) srcs/main.c libft_malloc_OSTTYPE.so -o test

clean:
	@echo "Cleaning"
	@make -C ./libft clean
	@$(RM) $(OBJS)
	@echo "Done"

fclean: clean
	@echo "Cleaning executable"
	@make -C ./libft fclean
	@$(RM) $(NAME)
	@echo "Done"

re: fclean all
