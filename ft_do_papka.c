/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_papka.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:11:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 20:20:27 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_hidden(char *name)
{
	long int slash_ind;

	if (!name)
		return (0);
	if (name[0] != '.')
		return (0);
	slash_ind = ft_str_find_char(name, '/');
	if (name[0] == '.' && (slash_ind == -1 ||
		slash_ind == (long int)ft_strlen(name) - 1))
		return (1);
	return (0);
}

void	ft_do_papka_print(char *dir_name, t_dir_info *dir_info)
{
	t_tree			*dir_tree;
	t_field_width	*width_info;

	width_info = NULL;
	dir_tree = ft_out_dir(dir_name, dir_info, &width_info);
	if (dir_tree)
	{
		if (dir_info->info_type != U)
			ft_printf("total %d\n", dir_tree->field->total);
		ft_print_dir_tree(dir_tree, dir_info,
						width_info, dir_tree->field->is_device);
		ft_free_t_tree(dir_tree);
		dir_tree = NULL;
	}
	if (dir_info->info_type != U)
	{
		free(width_info);
		width_info = NULL;
	}
}

void	ft_do_papka_rec(char *dir_name,
						t_dir_info *dir_info,
						int *there_is_dirs_in_dir)
{
	t_lis			*names_in_dir;
	t_lis			*tmp;
	char			*full_name;

	names_in_dir = NULL;
	if (dir_info->is_rec)
	{
		*there_is_dirs_in_dir = ft_insert_all_dir_names_rec(dir_name,
															&names_in_dir,
															dir_info);
		ft_sort_by(dir_name, &names_in_dir, dir_info->sort_order);
		if (there_is_dirs_in_dir != 0)
		{
			tmp = names_in_dir;
			while (tmp)
			{
				full_name = ft_get_next_dir_name(dir_name, tmp->val);
				ft_printf("\n%s:\n", full_name);
				ft_do_papka(full_name, dir_info);
				ft_strdel(&full_name);
				tmp = tmp->next;
			}
		}
		ft_delete_list(&names_in_dir);
		names_in_dir = NULL;
	}
}

void	ft_do_papka(char *dir_name, t_dir_info *dir_info)
{
	int	there_is_dirs_in_dir;

	there_is_dirs_in_dir = 0;
	ft_do_papka_print(dir_name, dir_info);
	ft_do_papka_rec(dir_name, dir_info, &there_is_dirs_in_dir);
	if (there_is_dirs_in_dir == 0)
		return ;
}
