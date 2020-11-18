/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_right_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:33:50 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/18 20:07:10 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_right_order_size(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_size > rhs_stat.st_size)
		return (1);
	else if (lhs_stat.st_size == rhs_stat.st_size)
		return (ft_is_right_order_by_alph(lhs, rhs, SIZE));
	else
		return (0);
}

int		ft_is_right_order_rsize(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs)
{
	if (lhs_stat.st_size < rhs_stat.st_size)
		return (1);
	else if (lhs_stat.st_size == rhs_stat.st_size)
		return (ft_is_right_order_by_alph(lhs, rhs, RSIZE));
	else
		return (0);
}

int		ft_is_right_order(char *parent_name,
							char *lhs, char *rhs,
							enum e_order_type order_type)
{
	struct stat	lhs_stat;
	struct stat	rhs_stat;
	char		*lhs_full;
	char		*rhs_full;

	lhs_full = ft_get_next_dir_name(parent_name, lhs);
	rhs_full = ft_get_next_dir_name(parent_name, rhs);
	lstat(lhs_full, &lhs_stat);
		// ft_lstat_error();
	lstat(rhs_full, &rhs_stat);
		// ft_lstat_error();
	ft_strdel(&lhs_full);
	ft_strdel(&rhs_full);
	if (order_type == ALPH)
		return (ft_is_right_order_by_alph(lhs, rhs, order_type));
	if (order_type == RALPH)
		return (ft_is_right_order_by_alph(lhs, rhs, order_type));
	if (order_type == TBITRH)
		return (ft_is_right_order_tbirth(lhs_stat, rhs_stat, lhs, rhs));
	if (order_type == RTBIRTH)
		return (ft_is_right_order_rtbirth(lhs_stat, rhs_stat, lhs, rhs));
	if (order_type == TMOD)
		return (ft_is_right_order_tmod(lhs_stat, rhs_stat, lhs, rhs));
	if (order_type == RTMOD)
		return (ft_is_right_order_rtmod(lhs_stat, rhs_stat, lhs, rhs));
	if (order_type == SIZE)
		return (ft_is_right_order_size(lhs_stat, rhs_stat, lhs, rhs));
	if (order_type == RSIZE)
		return (ft_is_right_order_rsize(lhs_stat, rhs_stat, lhs, rhs));
	// if (order_type == ORGN)
	// 	return (1);
	return (0);
}
