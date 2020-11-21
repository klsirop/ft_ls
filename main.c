/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:08:39 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 16:04:26 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_next_dir_name(char *start, char *end)
{
	char *tmp;
	char *full;

	if (!start)
	{
		if (!(full = ft_strdup(end)))
			ft_malloc_error();
		return (full);
	}
	tmp = ft_strconcat(start, "/");
	full = ft_strconcat(tmp, end);
	ft_strdel(&tmp);
	return (full);
}

void	ft_out_dirs(t_info *info, t_dir_info *dir_info)
{
	t_lis	*tmp;
	int		is_first;

	// ft_printf("sort\n");
	ft_sort_by(NULL, &(info->dir_names), dir_info->sort_order);
	is_first = 1;
	tmp = info->dir_names;
	while (tmp)
	{
		if (!is_first)
			ft_printf("\n");
		if (is_first)
			is_first = 0;
		if (!(tmp == info->dir_names && tmp->next == NULL)
			|| info->deleted_dir == 1 || info->file_names)
			ft_printf("%s:\n", tmp->val);
		ft_do_papka(tmp->val, dir_info);
		tmp = tmp->next;
	}
}

void	ft_out_argc(t_info *info, t_dir_info *dir_info)
{
	ft_separate_files_and_dirs(info, dir_info);
	ft_out_files(info, dir_info);
	if (info->dir_names && info->file_names)
		ft_printf("\n");
	ft_out_dirs(info, dir_info);
}

int		main(int argc, char *argv[])
{
	t_info		*info;
	t_dir_info	*dir_info;

	info = NULL;
	dir_info = NULL;
	ft_init_info(&info);
	ft_parse_input(argc, argv, info);
	ft_manage_flags_overlap(info);
	ft_is_right_dir_names(info);
	ft_init_dir_info(&dir_info);
	ft_find_sort_order(dir_info, info);
	ft_find_info_type(dir_info, info);
	ft_find_is_r(dir_info, info);
	ft_find_is_hidden(dir_info, info);
	ft_out_argc(info, dir_info);
	ft_free_t_info(&info);
	ft_free_t_dir_info(&dir_info);
	return (0);
}
