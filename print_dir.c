#include "ft_ls.h"

void	ft_find_all_width(t_file_info *file_info, t_field_width *width_info) {
	t_file_info *tmp;
	char *str_tmp;
	int len;

	tmp = file_info;
	while (tmp) {
		str_tmp = ft_itoa(tmp->hard_links);
		len = ft_strlen(str_tmp);
		if (width_info->hard_links < len)
			width_info->hard_links = len;
		ft_strdel(&str_tmp);

		len = ft_strlen(tmp->usr_name);
		if (width_info->user < len)
			width_info->user = len;

		len = ft_strlen(tmp->grp_name);
		if (width_info->group < len)
			width_info->group = len;

		str_tmp = ft_itoa(tmp->file_size);
		len = ft_strlen(str_tmp);
		if (width_info->size < len)
			width_info->size = len;
		ft_strdel(&str_tmp);

		len = ft_strlen(tmp->time->month);
		if (width_info->mounth < len)
			width_info->mounth = len;

		len = ft_strlen(tmp->time->day);
		// ft_printf("len: %d day: %s\n", len, tmp->time->day);
		if (width_info->day < len)
			width_info->day = len;

		len = ft_strlen(tmp->file_name);
		// ft_printf("filename: %s\n", tmp->file_name);
		if (width_info->filename < len)
			width_info->filename = len;

		if (tmp->link_name) {
			len = ft_strlen(tmp->link_name);
			if (width_info->linkname < len)
				width_info->linkname = len;
		}

		if (tmp->time->year) {
			len = ft_strlen(tmp->time->year);
			if (width_info->time < len)
				width_info->time = len;
		} else {
			if (width_info->time < 5)
				width_info->time = 5;
		}

		tmp = tmp->next;
	}
	if (width_info->day < 2)
		width_info->day = 2;
}

void	ft_init_width_info(t_field_width *width_info) {
	width_info->day = 0;
	width_info->filename = 0;
	width_info->group = 0;
	width_info->hard_links = 0;
	width_info->linkname = 0;
	width_info->mounth = 0;
	width_info->size = 0;
	width_info->user = 0;
}

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
	// ft_printf("%s\n", full_arg);
	ft_printf(full_arg, str);
	ft_strdel(&full_arg);
}

void	ft_print_hour_min(char *hour, char *min, int wid) {
	char *hour_c;
	char *hour_c_min;

	hour_c = ft_strconcat(hour, ":");
	hour_c_min = ft_strconcat(hour_c, min);
	ft_strdel(&hour_c);
	ft_printf_width(hour_c_min, wid, 0);
	ft_strdel(&hour_c_min);
}

void	ft_output_l(t_dir_info* dir_info, t_file_info *file_info, int is_dir) {
	t_field_width *width_info;
	t_file_info *tmp;
	char *tmp_str;


	width_info = (t_field_width *)malloc(sizeof(t_field_width));
	ft_init_width_info(width_info);
	ft_find_all_width(file_info, width_info);
	// ft_printf("hard links: %d\n", width_info->hard_links);
	// ft_printf("name: %d\n", width_info->filename);

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
			ft_printf_width(tmp->usr_name, width_info->user, 0);
			ft_printf("  ");
		}
		if (dir_info->info_type != LO && dir_info->info_type != LOG) {
			ft_printf("%s", tmp->grp_name);
			ft_printf("  ");
		}
		if (dir_info->info_type == LOG) {
			ft_printf("  ");
		}

		
		tmp_str = ft_itoa(tmp->file_size);
		ft_printf_width(tmp_str, width_info->size, 0);
		ft_strdel(&tmp_str);

		ft_printf(" ");
		ft_printf_width(tmp->time->month, width_info->mounth, 0);
		ft_printf(" ");
		ft_printf_width(tmp->time->day, width_info->day, 0);
		ft_printf(" ");

		if (tmp->time->hour) {
			// ft_print_hour_min(tmp->time->hour, tmp->time->min, width_info->time);
			ft_printf("%s:%s", tmp->time->hour, tmp->time->min);
		} else {
			ft_printf(" %s", tmp->time->year);
			// ft_printf_width(tmp->time->year, width_info->time, 0);
		}

		ft_printf(" ");
		ft_printf("%s", tmp->file_name);

		if (tmp->link_name) {
			ft_printf(" -> ");
			ft_printf_width(tmp->link_name, width_info->linkname, 0);
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
		// ft_printf("OK\n");
		if (dir_info->info_type == U) {
			if (!is_first) {
				ft_printf("\n");
			}
			if (is_first)
				is_first = 0;

			ft_printf("%s", tmp->file_name);
		}
		// } else if (dir_info->info_type == L) {

		// 	ft_printf("%c", tmp->rights->mode);
		// 	ft_printf("%s", tmp->rights->usr_rights);
		// 	ft_printf("%s", tmp->rights->grp_rights);
		// 	ft_printf("%s", tmp->rights->oth_rights);
		// 	ft_printf("%c", tmp->rights->acl);

		// 	// ft_printf(" ");

		// 	ft_printf("%lu", tmp->hard_links);

		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->usr_name);
		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->grp_name);

		// 	ft_printf(" ");
		// 	ft_printf("%ld", tmp->file_size);

		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->time->month);
		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->time->day);
		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->time->hour);
		// 	ft_printf(":");
		// 	ft_printf("%s", tmp->time->min);

		// 	ft_printf(" ");
		// 	ft_printf("%s", tmp->file_name);

		// 	if (tmp->link_name) {
		// 		ft_printf(" -> ");
		// 		ft_printf("%s", tmp->link_name);
		// 	}

		// 	ft_printf("\n");
		// }
		tmp = tmp->next;
	}

	if (dir_info->info_type == U && file_info != NULL) {
		ft_printf("\n");
	}
}
