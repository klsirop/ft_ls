/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_info_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:19:23 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 14:44:06 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_further(char *str, char c, char *compare)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (1);
		else if (ft_strchr(compare, str[i]))
			return (0);
		i--;
	}
	return (0);
}

int		ft_check_list_types(t_dir_info *dir_info, t_info *info)
{
	if (ft_strchr(info->flags, 'g'))
	{
		dir_info->info_type = LG;
		return (1);
	}
	if (ft_strchr(info->flags, 'o'))
	{
		dir_info->info_type = LO;
		return (1);
	}
	if (ft_strchr(info->flags, 'l'))
	{
		dir_info->info_type = L;
		return (1);
	}
	return (0);
}

void	ft_find_info_type(t_dir_info *dir_info, t_info *info)
{
	if (!info->flags)
	{
		dir_info->info_type = U;
		return ;
	}
	if (ft_strchr(info->flags, 'U'))
		dir_info->is_birth_time = 1;
	if (ft_strchr(info->flags, '1') && ft_is_further(info->flags, '1', "lgo"))
	{
		dir_info->info_type = U;
		return ;
	}
	if (ft_strchr(info->flags, 'g') && ft_strchr(info->flags, 'o'))
	{
		dir_info->info_type = LOG;
		return ;
	}
	if (ft_check_list_types(dir_info, info) == 1)
		return ;
	dir_info->info_type = U;
}

void	ft_find_is_r(t_dir_info *dir_info, t_info *info)
{
	if (!info->flags)
	{
		dir_info->is_rec = 0;
		return ;
	}
	if (ft_strchr(info->flags, 'R'))
		dir_info->is_rec = 1;
	else
		dir_info->is_rec = 0;
}

void	ft_find_is_hidden(t_dir_info *dir_info, t_info *info)
{
	if (!info->flags)
	{
		dir_info->is_hidden = 0;
		return ;
	}
	if (ft_strchr(info->flags, 'a') || ft_strchr(info->flags, 'f'))
		dir_info->is_hidden = 1;
	else
		dir_info->is_hidden = 0;
}
