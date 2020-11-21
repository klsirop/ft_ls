/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:14:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 21:14:13 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_add_begin(t_lis **head, char *str)
{
	t_lis *tmp;

	if (*head == NULL)
	{
		if (!(*head = (t_lis *)malloc(sizeof(t_lis))))
			ft_malloc_error();
		if (!((*head)->val = ft_strdup(str)))
			ft_malloc_error();
		(*head)->next = NULL;
	}
	else
	{
		if (!(tmp = (t_lis *)malloc(sizeof(t_lis))))
			ft_malloc_error();
		if (!(tmp->val = ft_strdup(str)))
			ft_malloc_error();
		tmp->next = *head;
		*head = tmp;
	}
}

void	ft_list_add(t_lis **head, char *str)
{
	t_lis *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		if (!(tmp = (t_lis *)malloc(sizeof(t_lis))))
			ft_malloc_error();
		if (!(tmp->val = ft_strdup(str)))
			ft_malloc_error();
		tmp->next = NULL;
		*head = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_lis *)malloc(sizeof(t_lis))))
			ft_malloc_error();
		tmp = tmp->next;
		if (!(tmp->val = ft_strdup(str)))
			ft_malloc_error();
		tmp->next = NULL;
	}
}

void	ft_file_list_add_begin(t_file_info **head, char *str)
{
	t_file_info *tmp;

	if (*head == NULL)
	{
		ft_init_file_info(head);
		if (!((*head)->file_name = ft_strdup(str)))
			ft_malloc_error();
		(*head)->next = NULL;
	}
	else
	{
		ft_init_file_info(&tmp);
		if (!(tmp->file_name = ft_strdup(str)))
			ft_malloc_error();
		tmp->next = *head;
		*head = tmp;
	}
}

void	ft_list_add_l_begin(t_file_info **head, t_file_info *new_el)
{
	t_file_info *tmp;

	if (*head == NULL)
		*head = new_el;
	else
	{
		tmp = new_el;
		tmp->next = *head;
		*head = tmp;
	}
}
