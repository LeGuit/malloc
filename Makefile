# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/02 13:44:47 by gwoodwar          #+#    #+#              #
#    Updated: 2016/08/04 13:56:57 by gwoodwar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

CC = 		gcc
NAME =		libft_malloc_$(HOSTTYPE).so
LINK =		libft_malloc.so
#FLAGS =		-Wall -Wextra -Werror -O2
INCLS = 	-I./includes -I./libft/includes
LIBFT = 	-L./libft -lft
SRCS_DIR =	srcs
OBJS_DIR =	objs
LIBS =		libft/libft.a

LIST =	malloc \
		malloc_reg \
		malloc_large \
		realloc \
		tools_is_malloc \
		show_alloc_mem	\
		free \
		free_op 

SRCS := $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(LIST)))
OBJS := $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(LIST)))

all: $(NAME)

libft/libft.a:
	make -C libft

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(FLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT)
	ln -sf $@ $(LINK)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLS) -o $@ -c $<

clean:
	/bin/rm -rf $(OBJS_DIR)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LINK)

re: fclean all

.PHONY: re clean fclean all
