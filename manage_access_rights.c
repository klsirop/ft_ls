/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_access_rights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:21:59 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/15 15:22:18 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_usr_rights(mode_t mode, t_file_info *file_info)
{
	mode = mode & S_IRWXU;
	if (S_IRUSR & mode)
		file_info->rights->usr_rights[0] = 'r';
	else
		file_info->rights->usr_rights[0] = '-';
	if (S_IWUSR & mode)
		file_info->rights->usr_rights[1] = 'w';
	else
		file_info->rights->usr_rights[1] = '-';
	if (S_IXUSR & mode)
		file_info->rights->usr_rights[2] = 'x';
	else
		file_info->rights->usr_rights[2] = '-';
}

void	ft_get_group_rights(mode_t mode, t_file_info *file_info)
{
	mode = mode & S_IRWXG;
	if (S_IRGRP & mode)
		file_info->rights->grp_rights[0] = 'r';
	else
		file_info->rights->grp_rights[0] = '-';
	if (S_IWGRP & mode)
		file_info->rights->grp_rights[1] = 'w';
	else
		file_info->rights->grp_rights[1] = '-';
	if (S_IXGRP & mode)
		file_info->rights->grp_rights[2] = 'x';
	else
		file_info->rights->grp_rights[2] = '-';
}

void	ft_get_other_rights(mode_t mode, t_file_info *file_info)
{
	mode = mode & S_IRWXO;
	if (S_IROTH & mode)
		file_info->rights->oth_rights[0] = 'r';
	else
		file_info->rights->oth_rights[0] = '-';
	if (S_IWOTH & mode)
		file_info->rights->oth_rights[1] = 'w';
	else
		file_info->rights->oth_rights[1] = '-';
	if (S_IXOTH & mode)
		file_info->rights->oth_rights[2] = 'x';
	else
		file_info->rights->oth_rights[2] = '-';
}
