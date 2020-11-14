#include "ft_ls.h"

void	ft_out_files(t_info* info, t_dir_info* dir_info) {
	t_file_info* file_info;
	t_lis* tmp;
	t_file_info *tmp_file_info;

	ft_sort_by(NULL, info->file_names, dir_info->sort_order);
	file_info = NULL;
	tmp = info->file_names;
	while (tmp) {
		if (dir_info->is_hidden == 0 && tmp->val[0] == '.') {
			tmp = tmp->next;
			continue;
		}
		if (dir_info->info_type == U) {
			ft_file_list_add(&file_info, tmp->val);
		} else {
			tmp_file_info = NULL;
			ft_init_file_info(&tmp_file_info);
			ft_print_like_l(NULL, tmp->val, dir_info, tmp_file_info);
			ft_file_list_add_l(&file_info, tmp_file_info);
		}
		tmp = tmp->next;
	}
	ft_print_dir(dir_info, file_info, 0);
	ft_free_t_file_info(&file_info);
}

char	*ft_get_next_dir_name(char *start, char *end) {
	char *tmp;
	char *full;

	if (!start) {
		full = ft_strdup(end);
		return full;
	}
	tmp = ft_strconcat(start, "/");
	full = ft_strconcat(tmp, end);
	ft_strdel(&tmp);
	return full;
}

// just output dir
void	ft_do_papka(char *dir_name, t_dir_info *dir_info) {
	static int count;
	t_file_info* file_info;
	int there_is_dirs_in_dir;
	t_lis *names_in_dir;
	t_lis *tmp;
	char *full_name;

	there_is_dirs_in_dir = 0;
	file_info = NULL;
	ft_out_dir(dir_name, dir_info, &file_info);
	ft_print_dir(dir_info, file_info, 1);
	ft_free_t_file_info(&file_info);

	names_in_dir = NULL;
	if (dir_info->is_rec) {
		there_is_dirs_in_dir = ft_insert_all_dir_names(dir_name, &names_in_dir, dir_info, 1);
		if (there_is_dirs_in_dir != 0) {
			tmp = names_in_dir;
			while (tmp) {
				full_name = ft_get_next_dir_name(dir_name, tmp->val);
				ft_printf("\n%s:\n", full_name);
				ft_do_papka(full_name, dir_info);
				ft_strdel(&full_name);
				tmp = tmp->next;
			}
		}
		ft_delete_list(&names_in_dir);
		names_in_dir = NULL;
	}
	if (there_is_dirs_in_dir == 0) {
		return ;
	}
}

void	ft_out_dirs(t_info* info, t_dir_info* dir_info) {
	t_lis* tmp;
	int is_first;

	ft_sort_by(NULL, info->dir_names, dir_info->sort_order);
	is_first = 1;
	tmp = info->dir_names;
	while (tmp) {
		if (!is_first) {
			ft_printf("\n");
		}
		if (is_first)
			is_first = 0;
		if (!(tmp == info->dir_names && tmp->next == NULL) || info->deleted_dir == 1)
			ft_printf("%s:\n", tmp->val);
		ft_do_papka(tmp->val, dir_info);
		tmp = tmp->next;
	}
}

void	ft_out_argc(t_info* info, t_dir_info* dir_info) {
	ft_separate_files_and_dirs(info);
	ft_out_files(info, dir_info);
	if (info->dir_names && info->file_names) {
		ft_printf("\n");
	}
	ft_out_dirs(info, dir_info);
}

int main(int argc, char *argv[]) {
	t_info *info;
	t_dir_info *dir_info;

	info = NULL;
	dir_info = NULL;
	ft_init_info(&info);
	ft_parse_input(argc, argv, info);
	ft_manage_flags_overlap(info);
	ft_is_right_dir_names(info);
	ft_init_dir_info(&dir_info);
	ft_find_sort_order(dir_info, info);
	ft_find_info_type(dir_info, info);
	ft_find_is_r(dir_info, info);
	ft_find_is_hidden(dir_info, info);
	ft_out_argc(info, dir_info);

	ft_free_t_info(&info);
	ft_free_t_dir_info(&dir_info);

	// ft_print_flags(info);
	// ft_print_input_names(info);
	// ft_print_sort_order(dir_info);
	// ft_print_info_type(dir_info);
	// ft_print_is_r(dir_info);
	// ft_print_is_hidden(dir_info);

	return (0);
}
