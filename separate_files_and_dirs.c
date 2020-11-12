#include "ft_ls.h"

int	ft_is_dir(char *name, mode_t mode) {
	char buf[256];
	struct stat status;
	mode_t link_mode;

	if (S_ISLNK(mode)) {
		ft_memset(buf, '\0', 256);
		readlink(name, buf, 255);
		// ft_printf("buf: %s\n", buf);
		//get buf rights - check is it dir
		lstat(buf, &status);
		link_mode = status.st_mode;
		if (S_ISDIR(link_mode))
			return (1);
		else
			return (0);
	}
	

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
		if (ft_is_dir(tmp->val, mode)) {
			ft_list_add(&(info->dir_names), tmp->val);
		} else {
			ft_list_add(&(info->file_names), tmp->val);
		}
		tmp = tmp->next;
	}
}
