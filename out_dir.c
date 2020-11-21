/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:44:31 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 16:31:23 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree	*ft_out_dir(char *name,
					t_dir_info *dir_info,
					t_field_width **width_info)
{
	t_tree			*dir_tree;
	DIR				*dir;
	struct dirent	*dirent;
	t_file_info		*tmp_file_info;
	int				total;

	if (dir_info->info_type != U)
	{
		if (!(*width_info = (t_field_width *)malloc(sizeof(t_field_width))))
			ft_malloc_error();
		ft_init_width_info(*width_info);
	}
	total = 0;
	dir = opendir(name);
	if (!dir)
	{
		ft_error_permission_denided(name);
		return (NULL);
	}
	dir_tree = NULL;
	while ((dirent = readdir(dir)) != NULL)
	{
		// ft_printf("%s\n", dirent->d_name);
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
		{
			total += ft_print_like_l(name, dirent->d_name, tmp_file_info);
			ft_find_first_width(width_info, tmp_file_info);
			ft_find_last_width(width_info, tmp_file_info);
		}
		dir_tree = ft_insert_tree_element(dir_tree, tmp_file_info,
											name, dir_info->sort_order);
		if (dir_info->info_type != U && tmp_file_info->is_device == 1)
			dir_tree->field->is_device = 1;
	}
	closedir(dir);
	if (dir_tree)
		dir_tree->field->total = total;
	if (dir_info->info_type != U)
	{
		if ((*width_info)->day < 2)
			(*width_info)->day = 2;
		(*width_info)->minor = 3;
		(*width_info)->major = 3;
	}
	return (dir_tree);
}
