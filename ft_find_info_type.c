#include "ft_ls.h"

void	ft_find_info_type(t_dir_info* dir_info, t_info* info) {

	if (!info->flags) {
		dir_info->info_type = U;
		return ;
	}

	if (ft_strchr(info->flags, 'l')) {
		if (ft_strchr(info->flags, 'u'))
			dir_info->info_type = LU;
		else
			dir_info->info_type = L;
	} else if (ft_strchr(info->flags, 'g')) {
		dir_info->info_type = G;
	} else {
		dir_info->info_type = U;
	}
}

void	ft_find_is_R(t_dir_info* dir_info, t_info* info) {
	if (!info->flags) {
		dir_info->is_Rec = 0;
		return ;
	}

	if (ft_strchr(info->flags, 'R'))
		dir_info->is_Rec = 1;
	else
		dir_info->is_Rec = 0;
}

void	ft_find_is_hidden(t_dir_info* dir_info, t_info* info) {
	if (!info->flags) {
		dir_info->is_Hidden = 0;
		return ;
	}

	if (ft_strchr(info->flags, 'a') || ft_strchr(info->flags, 'f'))
		dir_info->is_Hidden = 1;
	else
		dir_info->is_Hidden = 0;
}
