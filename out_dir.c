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
	// insert
	this = NULL;
	dir = opendir(name);
	if (!dir) {
		// ft_error_permission_denided(name);
		return -1;
	}
	// ft_printf("okokokokok\n");
	while ((dirent = readdir(dir)) != NULL) {
		// ft_printf("\nIN FUNC dirent: %s\n", dirent->d_name);
		full_name = ft_get_next_dir_name(name, dirent->d_name);
		if (!is_only_dirs || ((ft_is_dir(full_name) && ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, "..")))) {
			if (is_only_dirs && dir_info->is_Hidden == 0 && dirent->d_name[0] == '.') {
				continue;
			}
			
			// ft_printf("OKAY DIR\n\n");
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
	// ft_printf("okkkk\n");
	closedir(dir);
	// ft_printf("okkkk\n");

	//sort
	ft_sort_by(*head, dir_info->sort_order);
	return res;
}

void	ft_out_dir(char* name, t_dir_info* dir_info, t_file_info **file_info) {
	t_lis *names_in_dir;
	t_lis *tmp;
	t_file_info *tmp_file_info;
	int total;

	names_in_dir = NULL;
	if (ft_insert_all_dir_names(name, &names_in_dir, dir_info, 0) == -1) {
		ft_error_permission_denided(name);
		return ;
	}
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
