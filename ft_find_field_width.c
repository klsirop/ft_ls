/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_field_width.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:48:01 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 18:49:04 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_find_device_width(
								t_field_width **width_info,
								t_file_info *tmp)
{
	char		*str_tmp;
	int			len;

	if (tmp->rights->mode != 'c')
	{
		if (!(str_tmp = ft_itoa(tmp->file_size)))
			ft_malloc_error();
		len = ft_strlen(str_tmp);
		if ((*width_info)->size < len)
			(*width_info)->size = len;
		ft_strdel(&str_tmp);
		return ;
	}
	if (!(str_tmp = ft_itoa(tmp->minor)))
		ft_malloc_error();
	len = ft_strlen(str_tmp);
	if ((*width_info)->minor < len)
		(*width_info)->minor = len;
	ft_strdel(&str_tmp);
	if (!(str_tmp = ft_itoa(tmp->major)))
		ft_malloc_error();
	len = ft_strlen(str_tmp);
	if ((*width_info)->major < len)
		(*width_info)->major = len;
	ft_strdel(&str_tmp);
}

void	ft_find_time_width(
								t_field_width **width_info,
								t_file_info *tmp)
{
	int			len;

	if (tmp->time->year)
	{
		len = ft_strlen(tmp->time->year);
		if ((*width_info)->time < len)
			(*width_info)->time = len;
	}
	else if ((*width_info)->time < 5)
	{
		(*width_info)->time = 5;
	}
	if (tmp->time_birth->year)
	{
		len = ft_strlen(tmp->time_birth->year);
		if ((*width_info)->time_birth < len)
			(*width_info)->time_birth = len;
	}
	else if ((*width_info)->time_birth < 5)
	{
		(*width_info)->time_birth = 5;
	}
}
