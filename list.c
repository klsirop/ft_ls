/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:10:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/16 18:52:42 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_delete_element(t_info **info, t_lis *prev)
{
	t_lis *tmp;

	if (prev == NULL)
	{
		tmp = (*info)->names;
		(*info)->names = tmp->next;
		ft_strdel(&(tmp->val));
		free(tmp);
		return ;
	}
	tmp = prev->next;
	prev->next = tmp->next;
	ft_strdel(&(tmp->val));
	free(tmp);
}

int		ft_find_list_len(t_lis *head)
{
	t_lis	*tmp;
	int		len;

	len = 0;
	tmp = head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int		ft_find_list_len_file_info(t_file_info *head)
{
	t_file_info	*tmp;
	int		len;

	len = 0;
	tmp = head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_print_list(t_lis *head)
{
	t_lis *tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("%s ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_delete_list(t_lis **head)
{
	t_lis *tmp;

	tmp = *head;
	while (*head)
	{
		*head = (*head)->next;
		ft_strdel(&(tmp->val));
		free(tmp);
		tmp = *head;
	}
}

void	ft_reverse_list(t_lis **head)
{
	t_lis *nex;
	t_lis *here;
	t_lis *tmp;

	here = *head;
	nex = NULL;
	while (here) {
		if (nex == NULL) {
			*head = here;
			return ;
		}
		if (here == *head)
			here->next = NULL;
		tmp = nex;
		nex = nex->next;
		tmp->next = here; 
		here = tmp;
	}
}

void	ft_reverse_list_file_info(t_file_info **head)
{
	t_file_info *nex;
	t_file_info *here;
	t_file_info *tmp;

	here = *head;
	nex = NULL;
	while (here) {
		if (nex == NULL) {
			*head = here;
			return ;
		}
		if (here == *head)
			here->next = NULL;
		tmp = nex;
		nex = nex->next;
		tmp->next = here; 
		here = tmp;
	}
}
