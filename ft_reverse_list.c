/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 21:12:34 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_change_pointers(t_lis **tmp,
							t_lis **nex,
							t_lis **here)
{
	*tmp = (*nex)->next;
	(*nex)->next = *here;
	*here = *tmp;
	*tmp = *nex;
}

void	ft_reverse_list(t_lis **head)
{
	t_lis *nex;
	t_lis *here;
	t_lis *tmp;

	here = *head;
	nex = NULL;
	while (here)
	{
		nex = here->next;
		if (here == *head)
			here->next = NULL;
		else
			here->next = tmp;
		if (nex == NULL)
		{
			*head = here;
			return ;
		}
		ft_change_pointers(&tmp, &nex, &here);
		if (here == NULL)
		{
			*head = tmp;
			return ;
		}
	}
}

void	ft_change_pointers_file_info(t_file_info **tmp,
							t_file_info **nex,
							t_file_info **here)
{
	*tmp = (*nex)->next;
	(*nex)->next = *here;
	*here = *tmp;
	*tmp = *nex;
}

void	ft_reverse_list_file_info(t_file_info **head)
{
	t_file_info *nex;
	t_file_info *here;
	t_file_info *tmp;

	here = *head;
	nex = NULL;
	while (here)
	{
		nex = here->next;
		if (here == *head)
			here->next = NULL;
		else
			here->next = tmp;
		if (nex == NULL)
		{
			*head = here;
			return ;
		}
		ft_change_pointers_file_info(&tmp, &nex, &here);
		if (here == NULL)
		{
			*head = tmp;
			return ;
		}
	}
}
