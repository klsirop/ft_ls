/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:54:55 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 20:58:30 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_size(struct stat *status, t_file_info *file_info)
{
	off_t size;

	if (file_info->rights->mode == 'c')
		return ;
	size = status->st_size;
	file_info->file_size = size;
}

void	ft_print_hard_links(struct stat status, t_file_info *file_info)
{
	nlink_t nlinks;

	nlinks = status.st_nlink;
	file_info->hard_links = nlinks;
}

void	ft_print_user_name(struct stat status, t_file_info *file_info)
{
	uid_t			st_uid;
	struct passwd	*pass;

	st_uid = status.st_uid;
	pass = getpwuid(st_uid);
	if (!pass)
	{
		if (!(file_info->usr_name = ft_itoa(st_uid)))
			ft_malloc_error();
	}
	else
	{
		if (!(file_info->usr_name = ft_strdup(pass->pw_name)))
			ft_malloc_error();
	}
}

void	ft_print_group_name(struct stat status, t_file_info *file_info)
{
	gid_t			st_gid;
	struct group	*gr;

	st_gid = status.st_gid;
	gr = getgrgid(st_gid);
	if (!gr)
	{
		if (!(file_info->grp_name = ft_itoa(st_gid)))
			ft_malloc_error();
	}
	else
	{
		if (!(file_info->grp_name = ft_strdup(gr->gr_name)))
			ft_malloc_error();
	}
}
