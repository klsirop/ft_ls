#include "ft_ls.h"

void	ft_find_sort_order(t_dir_info* dir_info, t_info* info) {
	if (!info->flags) {
		dir_info->sort_order = ALPH;
		return ;
	}

	if (ft_strchr(info->flags, 'U')) {
		if (!ft_strchr(info->flags, 't') || ft_flag_order('t', 'U', info->flags))
			dir_info->sort_order = ORGN;
		else
			dir_info->sort_order = TMOD;
		return ;
	}

	if (ft_strchr(info->flags, 'f')) {
		if (!ft_strchr(info->flags, 't') || ft_flag_order('t', 'f', info->flags))
			dir_info->sort_order = ORGN;
		else
			dir_info->sort_order = TMOD;
		return ;
	}

	if (ft_strchr(info->flags, 'S')) {
		if (ft_strchr(info->flags, 'r'))
			dir_info->sort_order = 	RSIZE;
		else
			dir_info->sort_order = SIZE;
		return ;
	}

	if (ft_strchr(info->flags, 't')) {
		if (ft_strchr(info->flags, 'r'))
			dir_info->sort_order = 	RTMOD;
		else
			dir_info->sort_order = TMOD;
		return ;
	}

	if (ft_strchr(info->flags, 'r')) {
		dir_info->sort_order = RALPH;
		return ;
	}
	else {
		dir_info->sort_order = 	ALPH;
		return ;
	}
	dir_info->sort_order= ORGN;
}
