#include "ft_ls.h"

int	ft_is_dir(char *name) {
	char buf[256];
	struct stat link_status;
	struct stat status;
	mode_t link_mode;
	mode_t mode;

	lstat(name, &status);
	mode = status.st_mode;
	if (S_ISLNK(mode)) {
		ft_memset(buf, '\0', 256);
		readlink(name, buf, 255);
		lstat(buf, &link_status);
		link_mode = link_status.st_mode;
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

/*
** separate files and dirs from 'info->names'
** write dirs to 'info->dir_names', files to 'info->file_names'
*/
void	ft_separate_files_and_dirs(t_info *info) {
	t_lis *tmp;
	struct stat status;
	mode_t mode;

	tmp = info->names;
	while (tmp) {
		lstat(tmp->val, &status);
		mode = status.st_mode;
		if (ft_is_dir(tmp->val))
			ft_list_add(&(info->dir_names), tmp->val);
		else
			ft_list_add(&(info->file_names), tmp->val);
		tmp = tmp->next;
	}
}
