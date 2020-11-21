/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 15:58:41 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		tmp = nex->next;
		nex->next = here;
		here = tmp;
		tmp = nex;
		if (here == NULL)
		{
			*head = tmp;
			return ;
		}
	}
}

void	ft_reverse_list_file_info(t_file_info **head)
{
	t_file_info *nex;
	t_file_info *here;
	t_file_info *tmp;

	// ft_printf("start: %s\n", (*head)->file_name);
	// ft_printf("start1: %s\n", ((*head)->next)->file_name);
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
		tmp = nex->next;
		nex->next = here;
		here = tmp;
		tmp = nex;
		if (here == NULL)
		{
			*head = tmp;
			return ;
		}
	}
}
