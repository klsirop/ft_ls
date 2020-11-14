#include "ft_ls.h"

void ft_free_after_split(char **arr) {
	int i;

	i = 0;
	while (arr[i]) {
		ft_strdel(&arr[i]);
		i++;
	}
}

void	ft_find_year_or_time(char **separate_date, char **separate_time, t_file_info* file_info) {
	time_t now_time;
	char *now_time_str;
	char **separate_now_time;
	char *now_year;
	char *file_year;

	now_time = time(&now_time);
	now_time_str = ft_strdup(ctime(&now_time));
	separate_now_time = ft_strsplit(now_time_str, ' ');
	ft_strdel(&now_time_str);

	now_year = ft_strsub(separate_now_time[4], 0, 4);
	file_year = ft_strsub(separate_date[4], 0, ft_strlen(separate_date[4]) - 1);

	if (!ft_strcmp(now_year, file_year)) {
		file_info->time->hour = ft_strdup(separate_time[0]);
		file_info->time->min = ft_strdup(separate_time[1]);
	} else {
		file_info->time->year = ft_strdup(file_year);
	}

	ft_strdel(&now_year);
	ft_strdel(&file_year);
	ft_free_after_split(separate_now_time);
	free(separate_now_time);
}

void	ft_print_time_modify(struct stat status, t_file_info* file_info) {
	time_t mtime;
	char *full_time;
	char **separate_date;
	char **separate_time;
	int is_need_year;

	ft_init_t_dtime(&(file_info->time));
	mtime = status.st_mtime;
	full_time = ft_strdup(ctime(&mtime));
	separate_date = ft_strsplit(full_time, ' ');
	ft_strdel(&full_time);
	separate_time = ft_strsplit(separate_date[3], ':');
	file_info->time->month = ft_strdup(separate_date[1]);
	file_info->time->day = ft_strdup(separate_date[2]);
	ft_find_year_or_time(separate_date, separate_time, file_info);
	ft_free_after_split(separate_time);
	ft_free_after_split(separate_date);
	free(separate_time);
	free(separate_date);
}