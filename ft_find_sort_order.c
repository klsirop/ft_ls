/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sort_order.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:31:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 17:53:58 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_check_first_sort_order(t_dir_info *dir_info, t_info *info)
{
	if (ft_strchr(info->flags, 'f'))
	{
		dir_info->sort_order = ORGN;
		return (1);
	}
	return (0);
}

int		ft_check_last_sort_order(t_dir_info *dir_info, t_info *info)
{
	if (ft_strchr(info->flags, 'S'))
	{
		if (ft_strchr(info->flags, 'r'))
			dir_info->sort_order = RSIZE;
		else
			dir_info->sort_order = SIZE;
		return (1);
	}
	if (ft_strchr(info->flags, 'U') && ft_strchr(info->flags, 't'))
	{
		if (ft_strchr(info->flags, 'r'))
			dir_info->sort_order = RTBIRTH;
		else
			dir_info->sort_order = TBITRH;
		return (1);
	}
	if (ft_strchr(info->flags, 't'))
	{
		if (ft_strchr(info->flags, 'r'))
			dir_info->sort_order = RTMOD;
		else
			dir_info->sort_order = TMOD;
		return (1);
	}
	return (0);
}

void	ft_find_sort_order(t_dir_info *dir_info, t_info *info)
{
	if (!info->flags)
	{
		dir_info->sort_order = ALPH;
		return ;
	}
	if (ft_check_first_sort_order(dir_info, info) == 1)
		return ;
	if (ft_check_last_sort_order(dir_info, info) == 1)
		return ;
	if (ft_strchr(info->flags, 'r'))
	{
		dir_info->sort_order = RALPH;
		return ;
	}
	else
	{
		dir_info->sort_order = ALPH;
		return ;
	}
	dir_info->sort_order = ORGN;
}
