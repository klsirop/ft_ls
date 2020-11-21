/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_right_dir_names.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:41:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 19:24:50 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error_nonexist_dir(t_lis *wrong_dirs)
{
	t_lis	*tmp;

	ft_sort_by(NULL, &wrong_dirs, ALPH);
	tmp = wrong_dirs;
	while (tmp)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(tmp->val, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		tmp = tmp->next;
	}
}

/*
** check that all names in info->names exists
** write wrong names into 'wrong dirs'
** delete wrong names from info->names
** sort 'wrong dirs'
** print about errors using 'wrong dirs'
*/

void	ft_is_right_dir_names(t_info *info)
{
	t_lis		*tmp;
	t_lis		*prev;
	t_lis		*wrong_dirs;
	struct stat	status;

	prev = NULL;
	tmp = info->names;
	wrong_dirs = NULL;
	while (tmp)
	{
		if (lstat(tmp->val, &status))
		{
			info->deleted_dir = 1;
			ft_list_add_begin(&wrong_dirs, tmp->val);
			ft_list_delete_element(&info, prev);
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
	ft_print_error_nonexist_dir(wrong_dirs);
	if (wrong_dirs)
		ft_delete_list(&wrong_dirs);
}
