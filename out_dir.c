/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:44:31 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 22:02:48 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*ft_out_dir_width(t_field_width **width_info,
			t_dir_info *dir_info,
			char *name)
{
	DIR	*dir;

	if (dir_info->info_type != U)
	{
		if (!(*width_info = (t_field_width *)malloc(sizeof(t_field_width))))
			ft_malloc_error();
		ft_init_width_info(*width_info);
	}
	dir = opendir(name);
	if (!dir)
	{
		ft_error_permission_denided(name);
		return (NULL);
	}
	return (dir);
}

void	ft_out_dir_last(t_tree *dir_tree,
			int total,
			t_dir_info *dir_info,
			t_field_width **width_info)
{
	if (dir_tree)
		dir_tree->field->total = total;
	if (dir_info->info_type != U)
	{
		if ((*width_info)->day < 2)
			(*width_info)->day = 2;
		(*width_info)->minor = 3;
		(*width_info)->major = 3;
	}
}

void	ft_out_dir_insert(t_tree **dir_tree,
			char *name, t_file_info
			*tmp_file_info,
			t_dir_info *dir_info)
{
	*dir_tree = ft_insert_tree_element(*dir_tree, tmp_file_info,
										name, dir_info->sort_order);
	if (dir_info->info_type != U && tmp_file_info->is_device == 1)
		(*dir_tree)->field->is_device = 1;
}

int		ft_width_total(char *name,
						t_file_info **tmp_file_info,
						t_field_width **width_info,
						struct dirent *dirent)
{
	int	total;

	total = 0;
	total += ft_print_like_l(name, dirent->d_name, *tmp_file_info);
	ft_find_first_width(width_info, *tmp_file_info);
	ft_find_last_width(width_info, *tmp_file_info);
	return (total);
}

void	ft_out_dir(char *name,
					t_dir_info *dir_info,
					t_field_width **width_info,
					t_tree **dir_tree)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_file_info		*tmp_file_info;
	int				total;

	total = 0;
	if (!(dir = ft_out_dir_width(width_info, dir_info, name)))
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (dir_info->is_hidden == 0 && ft_is_hidden(dirent->d_name))
			continue;
		tmp_file_info = NULL;
		ft_init_file_info(&tmp_file_info);
		if (dir_info->info_type == U)
		{
			if (!(tmp_file_info->file_name = ft_strdup(dirent->d_name)))
				ft_malloc_error();
		}
		else
			total += ft_width_total(name, &tmp_file_info, width_info, dirent);
		ft_out_dir_insert(dir_tree, name, tmp_file_info, dir_info);
	}
	closedir(dir);
	ft_out_dir_last(*dir_tree, total, dir_info, width_info);
}
