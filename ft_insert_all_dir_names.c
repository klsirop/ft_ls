/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_all_dir_names.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:49:14 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 20:29:10 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_check_dir(t_dir_info *dir_info,
		struct dirent *dirent,
		t_lis **head,
		t_lis **this)
{
	t_lis			*tmp;

	if (dir_info->is_hidden == 0 && dirent->d_name[0] == '.')
		return (-1);
	if (!(tmp = (t_lis *)malloc(sizeof(t_lis))))
		ft_malloc_error();
	if (!(tmp->val = ft_strdup(dirent->d_name)))
		ft_malloc_error();
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
		(*this)->next = tmp;
	*this = tmp;
	return (0);
}

int		ft_is_usual_dir(char *name,
						t_dir_info *dir_info,
						struct dirent *dirent)
{
	char			*full_name;

	full_name = ft_get_next_dir_name(name, dirent->d_name);
	if ((ft_is_dir(full_name, dir_info) &&
		ft_strcmp(dirent->d_name, ".") &&
		ft_strcmp(dirent->d_name, "..")))
	{
		ft_strdel(&full_name);
		return (1);
	}
	ft_strdel(&full_name);
	return (0);
}

int		ft_insert_all_dir_names_rec(char *name,
								t_lis **head,
								t_dir_info *dir_info)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_lis			*this;
	int				res;

	res = 0;
	this = NULL;
	if (!(dir = opendir(name)))
		return (-1);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_is_usual_dir(name, dir_info, dirent))
		{
			if (ft_check_dir(dir_info, dirent, head, &this) == -1)
				continue ;
			res = 1;
		}
	}
	closedir(dir);
	return (res);
}
