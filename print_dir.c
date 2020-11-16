#include "ft_ls.h"

void	ft_printf_width(char *str, int width, int is_left) {
	char *arg;
	char *full_arg;
	char *num_width;

	num_width = ft_itoa(width);
	if (!is_left)
		arg = ft_strconcat("%", num_width);
	else
		arg = ft_strconcat("%-", num_width);

	ft_strdel(&num_width);

	full_arg = ft_strconcat(arg, "s");
	ft_strdel(&arg);
	ft_printf(full_arg, str);
	ft_strdel(&full_arg);
}

int	ft_max(int a, int b)
{
	return a > b ? a : b;
}

void	ft_output_l(t_dir_info* dir_info, t_file_info *file_info, int is_dir) {
	t_field_width *width_info;
	t_file_info *tmp;
	char *tmp_str;

	width_info = NULL;
	ft_find_all_width(file_info, &width_info);
	width_info->minor = 3;
	width_info->major = 3;
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

		tmp_str = ft_itoa(tmp->hard_links);
		ft_printf_width(tmp_str, width_info->hard_links, 0);
		ft_strdel(&tmp_str);
		ft_printf(" ");

		if (dir_info->info_type != LG && dir_info->info_type != LOG) {
			ft_printf_width(tmp->usr_name, width_info->user, 1);
			ft_printf("  ");
		}
		if (dir_info->info_type != LO && dir_info->info_type != LOG) {
			ft_printf_width(tmp->grp_name, width_info->group, 1);
			ft_printf("  ");
		}
		if (dir_info->info_type == LOG) {
			ft_printf("  ");
		}

		if (tmp->rights->mode != 'c' && tmp->rights->mode != 'b') {
			tmp_str = ft_itoa(tmp->file_size);
			if (file_info->is_device == 1) {
				ft_printf_width(tmp_str, ft_max(width_info->size, width_info->minor) + 1 + width_info->major + 1, 0);
			}
			else
				ft_printf_width(tmp_str, width_info->size, 0);
			ft_strdel(&tmp_str);
			ft_printf(" ");
		} else {
			tmp_str = ft_itoa(tmp->major);
			ft_printf_width(tmp_str, width_info->major, 0);
			ft_strdel(&tmp_str);
			ft_printf(", ");
			tmp_str = ft_itoa(tmp->minor);
			ft_printf_width(tmp_str, width_info->minor, 0);
			ft_strdel(&tmp_str);
			ft_printf(" ");
		}

		ft_printf_width(tmp->time->month, width_info->mounth, 0);
		ft_printf(" ");
		ft_printf_width(tmp->time->day, width_info->day, 0);
		ft_printf(" ");

		if (tmp->time->hour) {
			ft_printf("%s:%s", tmp->time->hour, tmp->time->min);
		} else {
			ft_printf(" %s", tmp->time->year);
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
