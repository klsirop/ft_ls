/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:25:47 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 14:58:46 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}

void	ft_print_dir(t_dir_info *dir_info, t_file_info *file_info, int is_dir)
{
	t_file_info	*tmp;
	int			is_first;

	if (dir_info->info_type != U)
	{
		ft_output_l(dir_info, file_info, is_dir);
		return ;
	}
	is_first = 1;
	tmp = file_info;
	while (tmp)
	{
		if (!is_first)
			ft_printf("\n");
		if (is_first)
			is_first = 0;
		ft_printf("%s", tmp->file_name);
		tmp = tmp->next;
	}
	if (file_info != NULL)
		ft_printf("\n");
}

void	ft_print_node_l_size(t_file_info *tmp,
							int is_device,
							t_field_width *width_info)
{
	if (tmp->rights->mode != 'c' && tmp->rights->mode != 'b')
	{
		if (is_device == 1)
			ft_printf("%*lld", ft_max(width_info->size, width_info->minor) +
									1 + width_info->major + 1, tmp->file_size);
		else
			ft_printf("%*lld", width_info->size, tmp->file_size);
		ft_printf(" ");
	}
	else
		ft_printf("%*d, %*d ", width_info->major,
					tmp->major, width_info->minor, tmp->minor);
}

void	ft_print_node_l(t_file_info *tmp,
						t_dir_info *dir_info,
						t_field_width *width_info,
						int is_device)
{
	ft_output_l_four_col(dir_info, tmp, width_info);
	ft_print_node_l_size(tmp, is_device, width_info);
	ft_output_l_time(dir_info, width_info, tmp);
}

void	ft_print_node(t_file_info *tmp,
						t_dir_info *dir_info,
						t_field_width *width_info,
						int is_device)
{
	if (dir_info->info_type != U)
	{
		ft_print_node_l(tmp, dir_info, width_info, is_device);
		ft_printf("\n");
		return ;
	}
	ft_printf("%s", tmp->file_name);
	ft_printf("\n");
}
