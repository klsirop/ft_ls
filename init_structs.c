/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:04:17 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 19:06:06 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_init_t_tree(t_tree **head)
{
	if (!((*head) = (t_tree *)malloc(sizeof(t_tree))))
		ft_malloc_error();
	(*head)->right = NULL;
	(*head)->left = NULL;
	(*head)->field = NULL;
}

void	ft_init_width_info(t_field_width *width_info)
{
	width_info->day = 0;
	width_info->day_birth = 0;
	width_info->filename = 0;
	width_info->group = 0;
	width_info->hard_links = 0;
	width_info->linkname = 0;
	width_info->mounth = 0;
	width_info->mounth_birth = 0;
	width_info->size = 0;
	width_info->user = 0;
	width_info->time = 0;
	width_info->time_birth = 0;
	width_info->major = 0;
	width_info->minor = 0;
}
