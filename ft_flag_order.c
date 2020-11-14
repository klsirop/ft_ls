/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_order.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:40:45 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/14 21:41:23 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_flag_order(char fflag, char sflag, char *flags)
{
	int len;

	len = ft_strlen(flags) - 1;
	while (len >= 0)
	{
		if (flags[len] == fflag)
			return (0);
		if (flags[len] == sflag)
			return (1);
		len--;
	}
	return (1);
}
