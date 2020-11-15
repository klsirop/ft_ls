/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:30:59 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/15 15:35:27 by volyvar-         ###   ########.fr       */
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

void	ft_sort_by(char *parent_name,
					t_lis *names,
					enum e_order_type sort_order)
{
	t_lis	*tmp;
	int		len;
	int		i;
	int		is_end_sorting;

	if (sort_order == ORGN)
		return ;
	len = ft_find_list_len(names);
	i = 0;
	is_end_sorting = 0;
	while (i < len && !is_end_sorting)
	{
		is_end_sorting = 1;
		tmp = names;
		while (tmp)
		{
			if (tmp && tmp->next &&
				!ft_is_right_order(parent_name, tmp, tmp->next, sort_order))
			{
				is_end_sorting = 0;
				ft_swap_list_elements(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
		i++;
	}
}
