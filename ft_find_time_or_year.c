/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_time_or_year.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:25 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/22 13:53:11 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_time_or_year_birth(time_t now_time,
								time_t bitime,
								char **separate_time,
								t_file_info *file_info)
{
	int days;
	int hyear;

	days = 60 * 60 * 24;
	hyear = 182;
	if (((now_time - bitime) / days)
							< hyear && (now_time - bitime) >= 0)
	{
		if (!(file_info->time_birth->hour = ft_strdup(separate_time[0])))
			ft_malloc_error();
		if (!(file_info->time_birth->min = ft_strdup(separate_time[1])))
			ft_malloc_error();
		return (1);
	}
	return (0);
}

void	ft_find_year_or_time_birth(char **separate_date,
								char **separate_time,
								t_file_info *file_info,
								time_t bitime)
{
	time_t	now_time;
	char	*now_time_str;
	char	**separate_now_time;
	char	*now_year;
	char	*file_year;

	now_time = time(NULL);
	if (!(now_time_str = ft_strdup(ctime(&now_time))))
		ft_malloc_error();
	separate_now_time = ft_strsplit(now_time_str, ' ');
	ft_strdel(&now_time_str);
	if (!(now_year = ft_strsub(separate_now_time[4], 0, 4)))
		ft_malloc_error();
	if (!(file_year = ft_strsub(separate_date[4],
						0, ft_strlen(separate_date[4]) - 1)))
		ft_malloc_error();
	if (!(ft_time_or_year_birth(now_time, bitime, separate_time, file_info)))
	{
		if (!(file_info->time_birth->year = ft_strdup(file_year)))
			ft_malloc_error();
	}
	ft_strdel(&now_year);
	ft_strdel(&file_year);
	ft_free_after_split(separate_now_time);
	free(separate_now_time);
}

int		ft_time_ot_year(time_t now_time,
						time_t mtime,
						t_file_info *file_info,
						char **separate_time)
{
	int days;
	int hyear;

	days = 60 * 60 * 24;
	hyear = 182;
	if (((now_time - mtime) / days) < hyear && (now_time - mtime) >= 0)
	{
		if (!(file_info->time->hour = ft_strdup(separate_time[0])))
			ft_malloc_error();
		if (!(file_info->time->min = ft_strdup(separate_time[1])))
			ft_malloc_error();
		return (1);
	}
	return (0);
}

void	ft_find_year_or_time(char **separate_date,
								char **separate_time,
								t_file_info *file_info,
								time_t mtime)
{
	time_t	now_time;
	char	*now_time_str;
	char	**separate_now_time;
	char	*now_year;
	char	*file_year;

	now_time = time(NULL);
	if (!(now_time_str = ft_strdup(ctime(&now_time))))
		ft_malloc_error();
	separate_now_time = ft_strsplit(now_time_str, ' ');
	ft_strdel(&now_time_str);
	if (!(now_year = ft_strsub(separate_now_time[4], 0, 4)))
		ft_malloc_error();
	if (!(file_year = ft_strsub(separate_date[4],
						0, ft_strlen(separate_date[4]) - 1)))
		ft_malloc_error();
	if (!(ft_time_ot_year(now_time, mtime, file_info, separate_time)))
	{
		if (!(file_info->time->year = ft_strdup(file_year)))
			ft_malloc_error();
	}
	ft_strdel(&now_year);
	ft_strdel(&file_year);
	ft_free_after_split(separate_now_time);
	free(separate_now_time);
}
