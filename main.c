#include "ft_ls.h"

void	ft_out_files(t_info* info, t_dir_info* dir_info) {
	t_file_info* file_info;
	t_lis* tmp;
	t_file_info *tmp_file_info;

	ft_sort_by(info->file_names, dir_info);
	file_info = NULL;
	tmp = info->file_names;
	while (tmp) {
		if (dir_info->is_Hidden == 0 && tmp->val[0] == '.') {
			tmp = tmp->next;
			continue;
		}
		if (dir_info->info_type == U) {
			ft_file_list_add(&file_info, tmp->val);
		} else if (dir_info->info_type == L) {
			tmp_file_info = NULL;
			ft_init_file_info(&tmp_file_info);
			ft_print_like_l(NULL, tmp->val, dir_info, tmp_file_info);
			// ft_printf("%s\n", tmp_file_info->rights->usr_rights);
			ft_file_list_add_l(&file_info, tmp_file_info);
		}
		tmp = tmp->next;
	}

	ft_print_dir(dir_info, file_info, 0);
	ft_free_t_file_info(&file_info);

}

void	ft_out_dirs(t_info* info, t_dir_info* dir_info) {
	t_file_info* file_info;
	t_lis* tmp;
	int is_first;

	file_info = NULL;
	ft_sort_by(info->dir_names, dir_info);

	is_first = 1;
	tmp = info->dir_names;
	while (tmp) {
		// ft_init_file_info(&file_info);


		if (!is_first) {
			ft_printf("\n");
		}
		if (is_first)
			is_first = 0;

		if (!(tmp == info->dir_names && tmp->next == NULL))
			ft_printf("%s:\n", tmp->val);
		// remember info
		ft_out_dir(tmp->val, dir_info, &file_info);

		// print info
		ft_print_dir(dir_info, file_info, 1);

		ft_free_t_file_info(&file_info);

		if (dir_info->is_Rec) {
			
		}

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
	// ft_init_file_info(&file_info);
	ft_parse_input(argc, argv, info);
	ft_is_right_dir_names(info);
	ft_init_dir_info(&dir_info);
	ft_find_sort_order(dir_info, info);
	ft_find_info_type(dir_info, info);
	ft_find_is_R(dir_info, info);
	ft_find_is_hidden(dir_info, info);
	ft_out_argc(info, dir_info);

	// ft_print_flags(info);
	// ft_print_input_names(info);
	// ft_print_sort_order(dir_info);
	// ft_print_info_type(dir_info);
	// ft_print_is_R(dir_info);
	// ft_print_is_hidden(dir_info);

	return (0);
}
