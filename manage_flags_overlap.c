/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags_overlap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:17:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 20:43:58 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** return last c's index
*/

int		ft_str_find_char(char *str, char c)
{
	int i;
	int ind;

	ind = -1;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
		{
			ind = i;
			return (ind);
		}
		i--;
	}
	return (ind);
}

int		ft_count_c_in_str(char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_delete_char_in_str(char **str, char c)
{
	char	*new_str;
	int		count_c;
	int		i;
	int		j;

	count_c = ft_count_c_in_str(*str, c);
	if (!(new_str = (char *)malloc(sizeof(char) *
		(ft_strlen(*str) - count_c + 1))))
		ft_malloc_error();
	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] != c)
		{
			new_str[j] = (*str)[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	ft_strdel(str);
	if (!(*str = ft_strdup(new_str)))
		ft_malloc_error();
	ft_strdel(&new_str);
}

/*
** The -1 and -l options all override each other;
** the last one specified determines the format used.
*/

void	ft_manage_flags_overlap(t_info *info)
{
	int ind_l;
	int ind_1;

	if (!info->flags)
		return ;
	ind_l = ft_str_find_char(info->flags, 'l');
	ind_1 = ft_str_find_char(info->flags, '1');
	if (ind_l == -1 || ind_1 == -1)
		return ;
	if (ind_l > ind_1)
		ft_delete_char_in_str(&(info->flags), '1');
	else
		ft_delete_char_in_str(&(info->flags), 'l');
}
