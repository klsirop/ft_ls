#include "ft_ls.h"

// last arg - all dirs and files OR ONLY DIRS
int	ft_insert_all_dir_names(char *name, t_lis **head, t_dir_info* dir_info, int is_only_dirs) {
	DIR* dir;
	struct dirent* dirent;
	t_lis *tmp;
	t_lis *this;
	int res;
	char *full_name;

	res = 0;
	this = NULL;
	dir = opendir(name);
	if (!dir) {
		return -1;
	}
	while ((dirent = readdir(dir)) != NULL) {
		full_name = ft_get_next_dir_name(name, dirent->d_name);
		if (!is_only_dirs || ((ft_is_dir(full_name) && ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, "..")))) {
			if (is_only_dirs && dir_info->is_hidden == 0 && dirent->d_name[0] == '.') {
				ft_strdel(&full_name);
				continue;
			}
			res = 1;
			tmp = (t_lis *)malloc(sizeof(t_lis));
			tmp->val = ft_strdup(dirent->d_name);
			tmp->next = NULL;

			if (*head == NULL) {
				*head = tmp;
			} else {
				this->next = tmp;
			}
			this = tmp;
		}
		ft_strdel(&full_name);
	}
	closedir(dir);
	// ft_print_list(*head);
	// ft_print_list(*head);
	// ft_print_sort_order(dir_info);
	// ft_sort_by(name, head, dir_info->sort_order); !!!
	// ft_print_list(*head);
	// ft_printf("here:\n");
	// ft_print_list(*head);
	return res;
}

int	ft_insert_all_dir_names_rec(char *name, t_lis **head, t_dir_info* dir_info, int is_only_dirs) {
	DIR* dir;
	struct dirent* dirent;
	t_lis *tmp;
	t_lis *this;
	int res;
	char *full_name;

	res = 0;
	this = NULL;
	dir = opendir(name);
	if (!dir) {
		return -1;
	}
	while ((dirent = readdir(dir)) != NULL) {
		full_name = ft_get_next_dir_name(name, dirent->d_name);
		if (!is_only_dirs || ((ft_is_dir(full_name) && ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, "..")))) {
			if (is_only_dirs && dir_info->is_hidden == 0 && dirent->d_name[0] == '.') {
				ft_strdel(&full_name);
				continue;
			}
			res = 1;
			tmp = (t_lis *)malloc(sizeof(t_lis));
			tmp->val = ft_strdup(dirent->d_name);
			tmp->next = NULL;

			if (*head == NULL) {
				*head = tmp;
			} else {
				this->next = tmp;
			}
			this = tmp;
		}
		ft_strdel(&full_name);
	}
	closedir(dir);
	// ft_print_list(*head);
	// ft_print_list(*head);
	// ft_print_sort_order(dir_info);
	ft_sort_by(name, head, dir_info->sort_order);
	// ft_print_list(*head);
	// ft_printf("here:\n");
	// ft_print_list(*head);
	return res;
}

void	ft_out_dir(char* name, t_dir_info* dir_info, t_file_info **file_info) {
	t_lis *names_in_dir;
	t_lis *tmp;
	t_file_info *tmp_file_info;
	int total;

	names_in_dir = NULL;
	if (ft_insert_all_dir_names(name, &names_in_dir, dir_info, 0) == -1) {
		ft_delete_list(&names_in_dir);
		names_in_dir = NULL;
		ft_error_permission_denided(name);
		return ;
	}

	total = 0;
	tmp = names_in_dir;
	while (tmp) {
		if (dir_info->is_hidden == 0 && tmp->val[0] == '.') {
			tmp = tmp->next;
			continue;
		}
		if (dir_info->info_type == U) {
			ft_file_list_add_begin(file_info, tmp->val);
		} else {
			tmp_file_info = NULL;
			ft_init_file_info(&tmp_file_info);
			total += ft_print_like_l(name, tmp->val, dir_info, tmp_file_info);
			ft_list_add_l_begin(file_info, tmp_file_info);
			if (tmp_file_info->is_device == 1)
				(*file_info)->is_device = 1;
		}
		tmp = tmp->next;
	}
	ft_sort_by_file_info(name, file_info, dir_info->sort_order);
	if (*file_info)
		(*file_info)->total = total;
	ft_delete_list(&names_in_dir);
}
