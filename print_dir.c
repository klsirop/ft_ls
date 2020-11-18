#include "ft_ls.h"

int	ft_max(int a, int b)
{
	return a > b ? a : b;
}

void	ft_output_l(t_dir_info* dir_info, t_file_info *file_info, int is_dir) {
	t_field_width *width_info;
	t_file_info *tmp;
	// char *tmp_str;

	width_info = NULL;
	ft_find_all_width(file_info, &width_info);
	// ft_printf("minor: %d major: %d\n", width_info->minor, width_info->major);

	if (file_info && is_dir) {
		ft_printf("total %d\n", file_info->total);
	}

	tmp = file_info;
	while (tmp) {
		
		ft_printf("%c", tmp->rights->mode);
		ft_printf("%s", tmp->rights->usr_rights);
		ft_printf("%s", tmp->rights->grp_rights);
		ft_printf("%s", tmp->rights->oth_rights);
		ft_printf("%c", tmp->rights->acl);
		ft_printf(" ");

		// tmp_str = ft_itoa(tmp->hard_links);
		// ft_printf_width(tmp_str, width_info->hard_links, 0);
		// ft_strdel(&tmp_str);
		ft_printf("%*hu ", width_info->hard_links, tmp->hard_links);

		if (dir_info->info_type != LG && dir_info->info_type != LOG)
			ft_printf("%-*s  ", width_info->user, tmp->usr_name);
		if (dir_info->info_type != LO && dir_info->info_type != LOG)
			ft_printf("%-*s  ", width_info->group, tmp->grp_name);
		if (dir_info->info_type == LOG) {
			ft_printf("  ");
		}

		if (tmp->rights->mode != 'c' && tmp->rights->mode != 'b') {
			if (file_info->is_device == 1)
				ft_printf("%*lld", ft_max(width_info->size, width_info->minor) + 1 + width_info->major + 1, tmp->file_size);
			else
				ft_printf("%*lld", width_info->size, tmp->file_size);
			ft_printf(" ");
		} else
			ft_printf("%*d, %*d ", width_info->major, tmp->major, width_info->minor, tmp->minor);

		if (dir_info->is_birth_time == 0) {
			ft_printf("%*s %*s ", width_info->mounth, tmp->time->month, width_info->day, tmp->time->day);

			if (tmp->time->hour) {
				ft_printf("%s:%s", tmp->time->hour, tmp->time->min);
			} else {
				ft_printf(" %s", tmp->time->year);
			}
		} else {
			ft_printf("%*s %*s ", width_info->mounth_birth, tmp->time_birth->month, width_info->day_birth, tmp->time_birth->day);

			if (tmp->time_birth->hour) {
				ft_printf("%s:%s", tmp->time_birth->hour, tmp->time_birth->min);
			} else {
				ft_printf(" %s", tmp->time_birth->year);
			}
		}

		ft_printf(" ");
		ft_printf("%s", tmp->file_name);

		if (tmp->link_name) {
			ft_printf(" -> ");
			// ft_printf_width(tmp->link_name, width_info->linkname, 0);
			ft_printf("%s", tmp->link_name);
		}

		ft_printf("\n");
		tmp = tmp->next;
	}
}

void	ft_print_dir(t_dir_info* dir_info, t_file_info *file_info, int is_dir) {
	t_file_info *tmp;
	int is_first;

	if (dir_info->info_type != U) {
		ft_output_l(dir_info, file_info, is_dir);
		return ;
	}
	is_first = 1;
	tmp = file_info;
	while (tmp) {
		if (!is_first) {
			ft_printf("\n");
		}
		if (is_first)
			is_first = 0;
		ft_printf("%s", tmp->file_name);
		tmp = tmp->next;
	}
	if (file_info != NULL) {
		ft_printf("\n");
	}
}

void	ft_print_node_l(t_file_info *tmp, t_dir_info *dir_info, t_field_width *width_info, int is_device) {

	ft_printf("%c", tmp->rights->mode);
	ft_printf("%s", tmp->rights->usr_rights);
	ft_printf("%s", tmp->rights->grp_rights);
	ft_printf("%s", tmp->rights->oth_rights);

	ft_printf("%c", tmp->rights->acl);

	ft_printf(" ");
	ft_printf("%*hu ", width_info->hard_links, tmp->hard_links);


	if (dir_info->info_type != LG && dir_info->info_type != LOG)
		ft_printf("%-*s  ", width_info->user, tmp->usr_name);
	if (dir_info->info_type != LO && dir_info->info_type != LOG)
		ft_printf("%-*s  ", width_info->group, tmp->grp_name);
	if (dir_info->info_type == LOG) {
		ft_printf("  ");
	}

	if (tmp->rights->mode != 'c' && tmp->rights->mode != 'b') {
		if (is_device == 1)
			ft_printf("%*lld", ft_max(width_info->size, width_info->minor) + 1 + width_info->major + 1, tmp->file_size);
		else
			ft_printf("%*lld", width_info->size, tmp->file_size);
		ft_printf(" ");
	} else
		ft_printf("%*d, %*d ", width_info->major, tmp->major, width_info->minor, tmp->minor);

	// ft_printf("birth: %d\n", dir_info->is_birth_time);
	if (dir_info->is_birth_time == 0) {
		ft_printf("%*s %*s ", width_info->mounth, tmp->time->month, width_info->day, tmp->time->day);

		if (tmp->time->hour) {
			ft_printf("%s:%s", tmp->time->hour, tmp->time->min);
		} else {
			ft_printf(" %s", tmp->time->year);
		}
	} else {
		ft_printf("%*s %*s ", width_info->mounth, tmp->time_birth->month, width_info->day, tmp->time_birth->day);

		if (tmp->time_birth->hour) {
			ft_printf("%s:%s", tmp->time_birth->hour, tmp->time_birth->min);
		} else {
			ft_printf(" %s", tmp->time_birth->year);
		}
	}



	ft_printf(" ");
	ft_printf("%s", tmp->file_name);

	if (tmp->link_name) {
		ft_printf(" -> ");
		ft_printf("%s", tmp->link_name);
	// ft_printf("\n");

	}
}

void	ft_print_node(t_file_info *tmp, t_dir_info *dir_info, t_field_width *width_info, int is_device) {
	if (dir_info->info_type != U) {
		ft_print_node_l(tmp, dir_info, width_info, is_device);
		ft_printf("\n");
		return ;
	}
	// ft_print_node_u(ft_printf("%s "));
	ft_printf("%s", tmp->file_name);
	ft_printf("\n");
	// if (width_info != NULL)
	// 	ft_printf("\n");
}
