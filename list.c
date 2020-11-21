/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:10:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 19:24:17 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_delete_element(t_info **info, t_lis *prev)
{
	t_lis *tmp;

	if (prev == NULL)
	{
		tmp = NULL;
		if ((*info)->names)
		{
			tmp = ((*info)->names)->next;
			ft_strdel(&(((*info)->names)->val));
			free((*info)->names);
		}
		(*info)->names = tmp;
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
	int			len;

	len = 0;
	tmp = head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
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
