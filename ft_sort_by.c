/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:05:54 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 22:16:15 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_sort_by_if(t_lis *tmp,
					char *parent_name,
					enum e_order_type sort_order)
{
	if (tmp && tmp->next &&
				!ft_is_right_order(parent_name, tmp->val,
				(tmp->next)->val, sort_order))
		return (1);
	return (0);
}

void	ft_sort_by(char *parent_name,
					t_lis **names,
					enum e_order_type sort_order)
{
	t_lis	*tmp;
	int		len;
	int		i;
	int		is_end_sorting;
	t_lis	*prev;

	if (sort_order == ORGN)
		return ;
	len = ft_find_list_len(*names);
	i = 0;
	is_end_sorting = 0;
	while (i < len && !is_end_sorting)
	{
		is_end_sorting = 1;
		prev = NULL;
		tmp = *names;
		while (tmp)
		{
			if (ft_sort_by_if(tmp, parent_name, sort_order))
				ft_swap_list_elements_new(names, prev, &tmp, &is_end_sorting);
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

int		ft_sort_by_file_info_if(t_file_info *tmp,
								char *parent_name,
								enum e_order_type sort_order)
{
	if (tmp && tmp->next &&
				!ft_is_right_order(parent_name, tmp->file_name,
				(tmp->next)->file_name, sort_order))
		return (1);
	return (0);
}

int		ft_check_origin(enum e_order_type sort_order,
						t_file_info **file_info)
{
	if (sort_order == ORGN)
	{
		ft_reverse_list_file_info(file_info);
		return (1);
	}
	return (0);
}

void	ft_sort_by_file_info(char *parent_name,
					t_file_info **file_info,
					enum e_order_type sort_order)
{
	t_file_info	*tmp;
	int			len;
	int			i;
	int			is_end_sorting;
	t_file_info	*prev;

	if (ft_check_origin(sort_order, file_info))
		return ;
	len = ft_find_list_len_file_info(*file_info);
	i = 0;
	is_end_sorting = 0;
	while (i < len && !is_end_sorting)
	{
		is_end_sorting = 1;
		prev = NULL;
		tmp = *file_info;
		while (tmp)
		{
			if (ft_sort_by_file_info_if(tmp, parent_name, sort_order))
				ft_swap_file_info(file_info, prev, &tmp, &is_end_sorting);
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
