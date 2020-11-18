/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:14:35 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 20:41:50 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_after_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_strdel(&arr[i]);
		i++;
	}
}

void	ft_print_time_modify(struct stat status, t_file_info *file_info)
{
	time_t	mtime;
	char	*full_time;
	char	**separate_date;
	char	**separate_time;

	ft_init_t_dtime(&(file_info->time));
	mtime = status.st_mtime;
	if (!(full_time = ft_strdup(ctime(&mtime))))
		ft_malloc_error();
	separate_date = ft_strsplit(full_time, ' ');
	ft_strdel(&full_time);
	separate_time = ft_strsplit(separate_date[3], ':');
	if (!(file_info->time->month = ft_strdup(separate_date[1])))
		ft_malloc_error();
	if (!(file_info->time->day = ft_strdup(separate_date[2])))
		ft_malloc_error();
	ft_find_year_or_time(separate_date, separate_time, file_info, mtime);
	ft_free_after_split(separate_time);
	ft_free_after_split(separate_date);
	free(separate_time);
	free(separate_date);
}

void	ft_print_time_birth(struct stat status, t_file_info *file_info)
{
	time_t	bitime;
	char	*full_time;
	char	**separate_date;
	char	**separate_time;

	ft_init_t_dtime(&(file_info->time_birth));
	bitime = status.st_birthtimespec.tv_sec;
	if (!(full_time = ft_strdup(ctime(&bitime))))
		ft_malloc_error();
	separate_date = ft_strsplit(full_time, ' ');
	ft_strdel(&full_time);
	separate_time = ft_strsplit(separate_date[3], ':');
	if (!(file_info->time_birth->month = ft_strdup(separate_date[1])))
		ft_malloc_error();
	if (!(file_info->time_birth->day = ft_strdup(separate_date[2])))
		ft_malloc_error();
	ft_find_year_or_time_birth(separate_date, separate_time, file_info, bitime);
	ft_free_after_split(separate_time);
	ft_free_after_split(separate_date);
	free(separate_time);
	free(separate_date);
}
