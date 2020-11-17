/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:14:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/16 19:03:25 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_add_begin(t_lis **head, char *str)
{
	t_lis *tmp;

	if (*head == NULL)
	{
		*head = (t_lis *)malloc(sizeof(t_lis));
		(*head)->val = ft_strdup(str);
		(*head)->next = NULL;
	}
	else
	{
		tmp = (t_lis *)malloc(sizeof(t_lis));
		tmp->val = ft_strdup(str);
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
		tmp = (t_lis *)malloc(sizeof(t_lis));
		tmp->val = ft_strdup(str);
		tmp->next = NULL;
		*head = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_lis *)malloc(sizeof(t_lis));
		tmp = tmp->next;
		tmp->val = ft_strdup(str);
		tmp->next = NULL;
	}
}

void	ft_file_list_add(t_file_info **head, char *str)
{
	t_file_info *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		ft_init_file_info(&tmp);
		tmp->file_name = ft_strdup(str);
		*head = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		ft_init_file_info(&(tmp->next));
		tmp = tmp->next;
		tmp->file_name = ft_strdup(str);
	}
}

void	ft_file_list_add_begin(t_file_info **head, char *str)
{
	t_file_info *tmp;

	if (*head == NULL)
	{
		ft_init_file_info(head);
		(*head)->file_name = ft_strdup(str);
		(*head)->next = NULL;
	}
	else
	{
		ft_init_file_info(&tmp);
		tmp->file_name = ft_strdup(str);
		tmp->next = *head;
		*head = tmp;
	}
}

void	ft_file_list_add_l(t_file_info **head, t_file_info *new_el)
{
	t_file_info *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		*head = new_el;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_el;
	}
}

void	ft_list_add_l_begin(t_file_info **head, t_file_info *new_el)
{
	t_file_info *tmp;

	if (*head == NULL)
	{
		*head = new_el;
		// *head = (t_lis *)malloc(sizeof(t_lis));
		// (*head)->val = ft_strdup(str);
		// (*head)->next = NULL;
	}
	else
	{
		// tmp = (t_lis *)malloc(sizeof(t_lis));
		// tmp->val = ft_strdup(str);
		tmp = new_el;
		tmp->next = *head;
		*head = tmp;
	}
}
