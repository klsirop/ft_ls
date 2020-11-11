#include "ft_ls.h"

int	ft_is_dir(mode_t mode) {
	mode = mode & S_IFMT;
	if (S_ISDIR(mode))
		return (1);
	else
		return (0);
}

void	ft_separate_files_and_dirs(t_info *info) {
	t_lis *tmp;
	struct stat status;
	mode_t mode;

	tmp = info->names;
	while (tmp) {
		lstat(tmp->val, &status);
		mode = status.st_mode;
		if (ft_is_dir(mode)) {
			ft_list_add(&(info->dir_names), tmp->val);
		} else {
			ft_list_add(&(info->file_names), tmp->val);
		}
		tmp = tmp->next;
	}
}
