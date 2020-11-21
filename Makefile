# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/01 17:44:02 by klsirop           #+#    #+#              #
#    Updated: 2020/11/21 15:12:28 by volyvar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L ./libft/ -lft
HEAD = ./ft_ls.h
LIBFT = ./libft/libft.a


SRC = 	main.c init.c parse_input.c list.c ft_add_char_to_string.c \
		error.c ft_is_right_dir_names.c \
		ft_find_sort_order.c init_structs.c ft_find_info_type.c \
		sort_names.c out_dir.c print_dir.c free.c print_like_l.c \
		separate_files_and_dirs.c manage_flags_overlap.c \
		manage_rights.c manage_file_time.c ft_find_all_width.c \
		list_add.c manage_access_rights.c ft_is_right_order.c \
		tree.c ft_find_field_width.c ft_is_right_order_by.c \
		ft_reverse_list.c ft_do_papka.c ft_out_files.c \
		ft_find_time_or_year.c ft_insert_all_dir_names.c \
		get_file_info.c ft_output_l.c

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
