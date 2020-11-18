/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_files_and_dirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:31 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 16:02:26 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_link_dir(char *name, mode_t mode)
{
	char		buf[256];
	mode_t		link_mode;
	struct stat	link_status;

	if (S_ISLNK(mode))
	{
		ft_memset(buf, '\0', 256);
		readlink(name, buf, 255);
		lstat(buf, &link_status);
		link_mode = link_status.st_mode;
		if (S_ISDIR(link_mode))
			return (1);
		else
			return (0);
	}
	return (-1);
}

int		ft_is_dir(char *name, t_dir_info *dir_info)
{
	struct stat	status;
	mode_t		mode;
	int			is_link_dir;

	lstat(name, &status);
	mode = status.st_mode;
	is_link_dir = ft_is_link_dir(name, mode);
	if (dir_info->info_type == U) {
		if (is_link_dir == 1)
			return (1);
		else if (is_link_dir == 0)
			return (0);
	} else if (is_link_dir != -1)
		return (0);
	mode = mode & S_IFMT;
	if (S_ISDIR(mode))
		return (1);
	else
		return (0);
}

/*
** separate files and dirs from 'info->names'
** write dirs to 'info->dir_names', files to 'info->file_names'
*/

void	ft_separate_files_and_dirs(t_info *info, t_dir_info *dir_info)
{
	t_lis		*tmp;
	struct stat	status;
	mode_t		mode;

	tmp = info->names;
	while (tmp)
	{
		lstat(tmp->val, &status);
		mode = status.st_mode;
		if (ft_is_dir(tmp->val, dir_info))
			ft_list_add_begin(&(info->dir_names), tmp->val);
		else
			ft_list_add_begin(&(info->file_names), tmp->val);
		tmp = tmp->next;
	}
}
