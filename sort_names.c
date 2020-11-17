/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:30:59 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/16 19:11:43 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap_list_elements(t_lis *here, t_lis *nex)
{
	char *tmp;

	tmp = ft_strdup(here->val);
	ft_strdel(&(here->val));
	here->val = ft_strdup(nex->val);
	ft_strdel(&(nex->val));
	nex->val = ft_strdup(tmp);
	ft_strdel(&tmp);
}

int		ft_is_right_order_by_alph(char *lhs,
									char *rhs,
									enum e_order_type order_type)
{
	if (order_type == ALPH || order_type == TMOD || order_type == SIZE)
	{
		if (ft_strcmp(lhs, rhs) > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ft_strcmp(lhs, rhs) < 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_swap_list_elements_new(t_lis **head, t_lis *prev, t_lis **here) {
	t_lis *nex;
	t_lis *tmp;

	nex = (*here)->next;
	if (prev == NULL) {
		*head = nex;
	}
	tmp = nex->next;
	nex->next = *here;
	(*here)->next = tmp;
	if (prev)
		prev->next = nex;
	// *here = (*here)->next;
}

void	ft_swap_list_elements_new_file_info(t_file_info **head, t_file_info *prev, t_file_info **here) {
	t_file_info *nex;
	t_file_info *tmp;

	nex = (*here)->next;
	if (prev == NULL) {
		*head = nex;
	}
	tmp = nex->next;
	nex->next = *here;
	(*here)->next = tmp;
	if (prev)
		prev->next = nex;
	// *here = (*here)->next;
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

	if (sort_order == ORGN) {
		ft_reverse_list(names);
		return ;
	}
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
			if (tmp && tmp->next &&
				!ft_is_right_order(parent_name, tmp->val, (tmp->next)->val, sort_order))
			{
				is_end_sorting = 0;
				ft_swap_list_elements_new(names, prev, &tmp);
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	ft_sort_by_file_info(char *parent_name,
					t_file_info **file_info,
					enum e_order_type sort_order)
{
	t_file_info	*tmp;
	int		len;
	int		i;
	int		is_end_sorting;
	t_file_info	*prev;

	if (sort_order == ORGN) {
		ft_reverse_list_file_info(file_info);
		return ;
	}
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
			if (tmp && tmp->next &&
				!ft_is_right_order(parent_name, tmp->file_name, (tmp->next)->file_name, sort_order))
			{
				is_end_sorting = 0;
				ft_swap_list_elements_new_file_info(file_info, prev, &tmp);
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
