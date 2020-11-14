#include "ft_ls.h"

void	ft_init_width_info(t_field_width *width_info) {
	width_info->day = 0;
	width_info->filename = 0;
	width_info->group = 0;
	width_info->hard_links = 0;
	width_info->linkname = 0;
	width_info->mounth = 0;
	width_info->size = 0;
	width_info->user = 0;
	width_info->time = 0;
}

void	ft_find_all_width(t_file_info *file_info, t_field_width **width_info) {
	t_file_info *tmp;
	char *str_tmp;
	int len;

	*width_info = (t_field_width *)malloc(sizeof(t_field_width));
	ft_init_width_info(*width_info);

	tmp = file_info;
	while (tmp) {
		str_tmp = ft_itoa(tmp->hard_links);
		len = ft_strlen(str_tmp);
		if ((*width_info)->hard_links < len)
			(*width_info)->hard_links = len;
		ft_strdel(&str_tmp);

		len = ft_strlen(tmp->usr_name);
		if ((*width_info)->user < len)
			(*width_info)->user = len;

		len = ft_strlen(tmp->grp_name);
		if ((*width_info)->group < len)
			(*width_info)->group = len;

		str_tmp = ft_itoa(tmp->file_size);
		len = ft_strlen(str_tmp);
		if ((*width_info)->size < len)
			(*width_info)->size = len;
		ft_strdel(&str_tmp);

		len = ft_strlen(tmp->time->month);
		if ((*width_info)->mounth < len)
			(*width_info)->mounth = len;

		len = ft_strlen(tmp->time->day);
		if ((*width_info)->day < len)
			(*width_info)->day = len;

		len = ft_strlen(tmp->file_name);
		if ((*width_info)->filename < len)
			(*width_info)->filename = len;

		if (tmp->link_name) {
			len = ft_strlen(tmp->link_name);
			if ((*width_info)->linkname < len)
				(*width_info)->linkname = len;
		}

		if (tmp->time->year) {
			len = ft_strlen(tmp->time->year);
			if ((*width_info)->time < len)
				(*width_info)->time = len;
		} else {
			if ((*width_info)->time < 5)
				(*width_info)->time = 5;
		}

		tmp = tmp->next;
	}
	if ((*width_info)->day < 2)
		(*width_info)->day = 2;
}