/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char_to_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:08:51 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 18:29:13 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_add_char_to_string(char **str, char c)
{
	char	*new_str;
	int		i;

	if (!(*str))
	{
		if (!(*str = (char *)malloc(sizeof(char) * 2)))
			ft_malloc_error();
		(*str)[0] = c;
		(*str)[1] = '\0';
		return ;
	}
	if (!(new_str = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2))))
		ft_malloc_error();
	i = 0;
	while ((*str)[i] != '\0')
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	ft_strdel(str);
	if (!(*str = ft_strdup(new_str)))
		ft_malloc_error();
	ft_strdel(&new_str);
}
