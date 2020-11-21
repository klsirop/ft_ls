/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_right_order_by.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:00:07 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 15:08:45 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_right_order_tmod(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_mtime > rhs_stat.st_mtime)
		return (1);
	else if (lhs_stat.st_mtime == rhs_stat.st_mtime)
		return (ft_is_right_order_by_alph(lhs, rhs, TMOD));
	else
		return (0);
}

int		ft_is_right_order_tbirth(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_birthtimespec.tv_sec > rhs_stat.st_birthtimespec.tv_sec)
		return (1);
	else if (lhs_stat.st_birthtimespec.tv_sec
			== rhs_stat.st_birthtimespec.tv_sec)
		return (ft_is_right_order_by_alph(lhs, rhs, TBITRH));
	else
		return (0);
}

int		ft_is_right_order_rtmod(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_mtime < rhs_stat.st_mtime)
		return (1);
	else if (lhs_stat.st_mtime == rhs_stat.st_mtime)
		return (ft_is_right_order_by_alph(lhs, rhs, RTMOD));
	else
		return (0);
}

int		ft_is_right_order_rtbirth(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_birthtimespec.tv_sec < rhs_stat.st_birthtimespec.tv_sec)
		return (1);
	else if (lhs_stat.st_birthtimespec.tv_sec
				== rhs_stat.st_birthtimespec.tv_sec)
		return (ft_is_right_order_by_alph(lhs, rhs, RTBIRTH));
	else
		return (0);
}
