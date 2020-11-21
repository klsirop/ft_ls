/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:33:34 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 17:00:48 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_output_l_four_col(t_dir_info *dir_info,
							t_file_info *tmp,
							t_field_width *width_info)
{
	ft_printf("%c", tmp->rights->mode);
	ft_printf("%s", tmp->rights->usr_rights);
	ft_printf("%s", tmp->rights->grp_rights);
	ft_printf("%s", tmp->rights->oth_rights);
	ft_printf("%c", tmp->rights->acl);
	ft_printf(" ");
	ft_printf("%*hu ", width_info->hard_links, tmp->hard_links);
	if (dir_info->info_type != LG && dir_info->info_type != LOG)
		ft_printf("%-*s  ", width_info->user, tmp->usr_name);
	if (dir_info->info_type != LO && dir_info->info_type != LOG)
		ft_printf("%-*s  ", width_info->group, tmp->grp_name);
	if (dir_info->info_type == LOG)
		ft_printf("  ");
}

void	ft_output_l_size(t_file_info *file_info,
						t_file_info *tmp,
						t_field_width *width_info)
{
	if (tmp->rights->mode != 'c' && tmp->rights->mode != 'b')
	{
		if (file_info->is_device == 1)
			ft_printf("%*lld",
				ft_max(width_info->size, width_info->minor) +
				1 + width_info->major + 1, tmp->file_size);
		else
			ft_printf("%*lld", width_info->size, tmp->file_size);
		ft_printf(" ");
	}
	else
		ft_printf("%*d, %*d ", width_info->major, tmp->major,
		width_info->minor, tmp->minor);
}

void	ft_output_l_time(t_dir_info *dir_info,
						t_field_width *width_info,
						t_file_info *tmp)
{
	if (dir_info->is_birth_time == 0)
	{
		ft_printf("%*s %*s ", width_info->mounth, tmp->time->month,
								width_info->day, tmp->time->day);
		if (tmp->time->hour)
			ft_printf("%s:%s", tmp->time->hour, tmp->time->min);
		else
			ft_printf(" %s", tmp->time->year);
	}
	else
	{
		ft_printf("%*s %*s ", width_info->mounth_birth,
				tmp->time_birth->month, width_info->day_birth,
										tmp->time_birth->day);
		if (tmp->time_birth->hour)
			ft_printf("%s:%s", tmp->time_birth->hour, tmp->time_birth->min);
		else
			ft_printf(" %s", tmp->time_birth->year);
	}
	ft_printf(" %s", tmp->file_name);
	if (tmp->link_name)
	{
		ft_printf(" -> ");
		ft_printf("%s", tmp->link_name);
	}
}

void	ft_output_l(t_dir_info *dir_info, t_file_info *file_info, int is_dir)
{
	t_field_width	*width_info;
	t_file_info		*tmp;

	width_info = NULL;
	ft_find_all_width(file_info, &width_info);
	if (file_info && is_dir)
		ft_printf("total %d\n", file_info->total);
	tmp = file_info;
	while (tmp)
	{
		ft_output_l_four_col(dir_info, tmp, width_info);
		ft_output_l_size(file_info, tmp, width_info);
		ft_output_l_time(dir_info, width_info, tmp);
		ft_printf("\n");
		tmp = tmp->next;
	}
	if (width_info)
		free(width_info);
}
