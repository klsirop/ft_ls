/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:30:59 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 22:14:20 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap_list_elements(t_lis *here, t_lis *nex)
{
	char *tmp;

	if (!(tmp = ft_strdup(here->val)))
		ft_malloc_error();
	ft_strdel(&(here->val));
	if (!(here->val = ft_strdup(nex->val)))
		ft_malloc_error();
	ft_strdel(&(nex->val));
	if (!(nex->val = ft_strdup(tmp)))
		ft_malloc_error();
	ft_strdel(&tmp);
}

int		ft_is_right_order_by_alph(char *lhs,
									char *rhs,
									enum e_order_type order_type)
{
	if (order_type == ALPH || order_type == TMOD ||
		order_type == SIZE || order_type == TBITRH)
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

void	ft_swap_list_elements_new(t_lis **head, t_lis *prev,
								t_lis **here, int *is_end_sorting)
{
	t_lis *nex;
	t_lis *tmp;

	nex = (*here)->next;
	if (prev == NULL)
		*head = nex;
	tmp = nex->next;
	nex->next = *here;
	(*here)->next = tmp;
	if (prev)
		prev->next = nex;
	*is_end_sorting = 0;
}

void	ft_swap_file_info(t_file_info **head,
											t_file_info *prev,
											t_file_info **here,
											int *is_end_sorting)
{
	t_file_info *nex;
	t_file_info *tmp;

	nex = (*here)->next;
	if (prev == NULL)
		*head = nex;
	tmp = nex->next;
	nex->next = *here;
	(*here)->next = tmp;
	if (prev)
		prev->next = nex;
	*is_end_sorting = 0;
}
