/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:09:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 19:04:44 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_init_info(t_info **info)
{
	if (!(*info = (t_info *)malloc(sizeof(t_info))))
		ft_malloc_error();
	(*info)->flags = NULL;
	(*info)->names = NULL;
	(*info)->dir_names = NULL;
	(*info)->file_names = NULL;
	(*info)->deleted_dir = 0;
}

void	ft_init_dir_info(t_dir_info **dir_info)
{
	if (!(*dir_info = (t_dir_info *)malloc(sizeof(t_dir_info))))
		ft_malloc_error();
	(*dir_info)->names = NULL;
	(*dir_info)->sort_order = 0;
	(*dir_info)->info_type = 0;
	(*dir_info)->is_rec = -1;
	(*dir_info)->is_hidden = -1;
	(*dir_info)->is_birth_time = 0;
}

void	ft_init_file_info(t_file_info **file_info)
{
	if (!((*file_info) = (t_file_info *)malloc(sizeof(t_file_info))))
		ft_malloc_error();
	(*file_info)->rights = NULL;
	(*file_info)->usr_name = NULL;
	(*file_info)->grp_name = NULL;
	(*file_info)->time = NULL;
	(*file_info)->time_birth = NULL;
	(*file_info)->link_name = NULL;
	(*file_info)->file_name = NULL;
	(*file_info)->next = NULL;
	(*file_info)->total = 0;
	(*file_info)->is_device = 0;
}

void	ft_init_t_rights(t_rights **rights)
{
	if (!((*rights) = (t_rights *)malloc(sizeof(t_rights))))
		ft_malloc_error();
	if (!((*rights)->usr_rights = (char *)malloc(sizeof(char) * 4)))
		ft_malloc_error();
	if (!((*rights)->grp_rights = (char *)malloc(sizeof(char) * 4)))
		ft_malloc_error();
	if (!((*rights)->oth_rights = (char *)malloc(sizeof(char) * 4)))
		ft_malloc_error();
	(*rights)->usr_rights[3] = '\0';
	(*rights)->grp_rights[3] = '\0';
	(*rights)->oth_rights[3] = '\0';
}

void	ft_init_t_dtime(t_dtime **time)
{
	if (!((*time) = (t_dtime *)malloc(sizeof(t_dtime))))
		ft_malloc_error();
	(*time)->month = NULL;
	(*time)->day = NULL;
	(*time)->hour = NULL;
	(*time)->min = NULL;
	(*time)->year = NULL;
}
