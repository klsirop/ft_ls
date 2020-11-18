/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:07:15 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 16:24:50 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_t_rights(t_rights **rights)
{
	if ((*rights)->usr_rights)
		ft_strdel(&(*rights)->usr_rights);
	if ((*rights)->grp_rights)
		ft_strdel(&(*rights)->grp_rights);
	if ((*rights)->oth_rights)
		ft_strdel(&(*rights)->oth_rights);
	free(*rights);
	*rights = NULL;
}

void	ft_free_t_dtime(t_dtime **time)
{
	if ((*time)->month)
		ft_strdel(&((*time)->month));
	if ((*time)->day)
		ft_strdel(&((*time)->day));
	if ((*time)->hour)
		ft_strdel(&((*time)->hour));
	if ((*time)->min)
		ft_strdel(&((*time)->min));
	if ((*time)->year)
		ft_strdel(&((*time)->year));
	free(*time);
	*time = NULL;
}

void	ft_free_t_file_info(t_file_info **head)
{
	t_file_info *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->rights)
			ft_free_t_rights(&(tmp->rights));
		if (tmp->usr_name)
			ft_strdel(&(tmp->usr_name));
		if (tmp->grp_name)
			ft_strdel(&(tmp->grp_name));
		if (tmp->time)
			ft_free_t_dtime(&(tmp->time));
		// ft_printf("okk\n");
		if (tmp->time_birth)
			ft_free_t_dtime(&(tmp->time_birth));
		// ft_printf("okk1\n");
		if (tmp->link_name)
			ft_strdel(&(tmp->link_name));
		if (tmp->file_name)
			ft_strdel(&(tmp->file_name));
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_t_info(t_info **info)
{
	if (!(*info))
		return ;
	if ((*info)->flags)
		ft_strdel(&((*info)->flags));
	if ((*info)->names)
		ft_delete_list(&((*info)->names));
	if ((*info)->file_names)
		ft_delete_list(&((*info)->file_names));
	if ((*info)->dir_names)
		ft_delete_list(&((*info)->dir_names));
	free(*info);
	*info = NULL;
}

void	ft_free_t_dir_info(t_dir_info **dir_info)
{
	if (!(*dir_info))
		return ;
	if ((*dir_info)->names)
		ft_delete_list(&((*dir_info)->names));
	free(*dir_info);
	*dir_info = NULL;
}
