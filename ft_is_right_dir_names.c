#include "ft_ls.h"

/*
** check that all names in info->names exists
** write wrong names into 'wrong dirs'
** delete wrong names from info->names
** sort 'wrong dirs'
** print about errors using 'wrong dirs'
*/
void	ft_is_right_dir_names(t_info* info) {
	t_lis* tmp;
	t_lis* prev;
	t_lis *wrong_dirs;
	struct stat status;

	prev = NULL;
	tmp = info->names;
	wrong_dirs = NULL;
	while (tmp) {
		if (lstat(tmp->val, &status)) {
			info->deleted_dir = 1;
			ft_list_add(&wrong_dirs, tmp->val);
			ft_list_delete_element(&info, prev);
			tmp = tmp->next;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
	}

	ft_sort_by(NULL, wrong_dirs, ALPH);
	tmp = wrong_dirs;
	while (tmp) {
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(tmp->val, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		tmp = tmp->next;
	}
	if (wrong_dirs)
		ft_delete_list(&wrong_dirs);
}
