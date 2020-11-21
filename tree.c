/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:37:27 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 22:04:29 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree	*ft_insert_tree_element(t_tree *head,
								t_file_info *new,
								char *parent_name,
								enum e_order_type order_type)
{
	int is_right_order;

	if (head == NULL)
	{
		ft_init_t_tree(&head);
		head->field = new;
	}
	else
	{
		is_right_order = ft_is_right_order(parent_name,
											head->field->file_name,
											new->file_name,
											order_type);
		if (is_right_order == 0)
			head->left = ft_insert_tree_element(head->left,
												new,
												parent_name,
												order_type);
		else
			head->right = ft_insert_tree_element(head->right,
												new,
												parent_name,
												order_type);
	}
	return (head);
}

void	ft_free_t_tree(t_tree *head)
{
	if (head != NULL)
	{
		ft_free_t_tree(head->left);
		ft_free_t_tree(head->right);
		ft_free_t_file_info(&(head->field));
		free(head);
	}
}

void	ft_print_dir_tree(t_tree *head,
							t_dir_info *dir_info,
							t_field_width *width_info,
							int is_device)
{
	if (head != NULL)
	{
		ft_print_dir_tree(head->left, dir_info, width_info, is_device);
		ft_print_node(head->field, dir_info, width_info, is_device);
		ft_print_dir_tree(head->right, dir_info, width_info, is_device);
	}
}

void	ft_just_print_tree(t_tree *head)
{
	if (head != NULL)
	{
		ft_just_print_tree(head->left);
		ft_printf("%s ", head->field->file_name);
		ft_just_print_tree(head->right);
	}
}
