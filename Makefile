# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/01 17:44:02 by klsirop           #+#    #+#              #
#    Updated: 2020/11/14 22:14:23 by volyvar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CFLAGS =
LDFLAGS = -L ./libft/ -lft
HEAD = ./ft_ls.h
LIBFT = ./libft/libft.a


SRC = 	main.c init.c parse_input.c list.c ft_add_char_to_string.c \
		error.c unnesessary_func.c ft_is_right_dir_names.c \
		ft_find_sort_order.c ft_flag_order.c ft_find_info_type.c \
		sort_names.c out_dir.c print_dir.c free.c print_like_l.c \
		separate_files_and_dirs.c manage_flags_overlap.c \
		manage_rights.c manage_file_time.c ft_find_all_width.c \
		list_add.c
# SRC =	error.c ft_add_char_to_string.c init.c \
# 		main.c parse_string.c list.c clean.c \
# 		ft_is_right_dir_names.c ft_find_sort_order.c \
# 		ft_flag_order.c print_things.c ft_find_info_type.c \
# 		out_name.c ft_print_like_l.c additional_func.c \
# 		sort_names.c find_place_in_list.c out_like_l.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C ./libft/

%.o: %.c $(HEAD)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(MAKE) -C ./libft/ $@
	@/bin/rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C ./libft/ $@
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
