/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:28:43 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 21:36:54 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_out_files_l(t_lis *tmp, t_file_info **file_info)
{
	t_file_info		*tmp_file_info;

	tmp_file_info = NULL;
	ft_init_file_info(&tmp_file_info);
	ft_print_like_l(NULL, tmp->val, tmp_file_info);
	ft_list_add_l_begin(file_info, tmp_file_info);
	if (tmp_file_info->is_device == 1)
		(*file_info)->is_device = 1;
}

void	ft_out_files(t_info *info, t_dir_info *dir_info)
{
	t_file_info		*file_info;
	t_lis			*tmp;

	file_info = NULL;
	tmp = info->file_names;
	while (tmp)
	{
		if (dir_info->is_hidden == 0 && ft_is_hidden(tmp->val))
		{
			tmp = tmp->next;
			continue;
		}
		if (dir_info->info_type == U)
			ft_file_list_add_begin(&file_info, tmp->val);
		else
		{
			ft_out_files_l(tmp, &file_info);
		}
		tmp = tmp->next;
	}
	ft_sort_by_file_info(NULL, &(file_info), dir_info->sort_order);
	ft_print_dir(dir_info, file_info, 0);
	ft_free_t_file_info(&file_info);
}
