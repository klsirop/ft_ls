/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_all_dir_names.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:49:14 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 20:49:30 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_insert_all_dir_names_rec(char *name,
								t_lis **head,
								t_dir_info *dir_info,
								int is_only_dirs)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_lis			*tmp;
	t_lis			*this;
	int				res;
	char			*full_name;

	res = 0;
	this = NULL;
	dir = opendir(name);
	if (!dir)
		return -1;
	while ((dirent = readdir(dir)) != NULL)
	{
		full_name = ft_get_next_dir_name(name, dirent->d_name);
		if (!is_only_dirs || ((ft_is_dir(full_name, dir_info)
			&& ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, ".."))))
		{
			if (is_only_dirs && dir_info->is_hidden == 0 && dirent->d_name[0] == '.')
			{
				ft_strdel(&full_name);
				continue;
			}
			res = 1;
			if (!(tmp = (t_lis *)malloc(sizeof(t_lis))))
				ft_malloc_error();
			if (!(tmp->val = ft_strdup(dirent->d_name)))
				ft_malloc_error();
			tmp->next = NULL;
			if (*head == NULL)
				*head = tmp;
			else
				this->next = tmp;
			this = tmp;
		}
		ft_strdel(&full_name);
	}
	closedir(dir);
	ft_sort_by(name, head, dir_info->sort_order);
	return res;
}