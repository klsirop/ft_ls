#include "ft_ls.h"

void	ft_insert_all_dir_names(char *name, t_lis **head, t_dir_info* dir_info) {
	DIR* dir;
	struct dirent* dirent;
	t_lis *tmp;
	t_lis *this;

	// insert
	this = NULL;
	dir = opendir(name);
	if (!dir) {
		ft_error_permission_denided(name);
	}
	// ft_printf("okokokokok\n");
	while ((dirent = readdir(dir)) != NULL) {
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
	// ft_printf("okkkk\n");
	closedir(dir);
	// ft_printf("okkkk\n");

	//sort
	ft_sort_by(*head, dir_info->sort_order);
}

void	ft_out_dir(char* name, t_dir_info* dir_info, t_file_info **file_info) {
	t_lis *names_in_dir;
	t_lis *tmp;
	t_file_info *tmp_file_info;
	int total;

	names_in_dir = NULL;
	ft_insert_all_dir_names(name, &names_in_dir, dir_info);
	// ft_printf("len: %d\n", ft_find_list_len(names_in_dir));

	total = 0;
	tmp = names_in_dir;
	while (tmp) {
			// ft_printf("%s\n", tmp->val);
		if (dir_info->is_Hidden == 0 && tmp->val[0] == '.') {
			tmp = tmp->next;
			continue;
		}
		if (dir_info->info_type == U) {
			ft_file_list_add(file_info, tmp->val);
		} else if (dir_info->info_type == L) {
			tmp_file_info = NULL;
			ft_init_file_info(&tmp_file_info);
			total += ft_print_like_l(name, tmp->val, dir_info, tmp_file_info);
			// ft_printf("%s\n", tmp_file_info->rights->usr_rights);
			ft_file_list_add_l(file_info, tmp_file_info);
		}
		tmp = tmp->next;
	}
	if (*file_info)
		(*file_info)->total = total;
}
