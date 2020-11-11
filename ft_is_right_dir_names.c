#include "ft_ls.h"

void	ft_is_right_dir_names(t_info* info) {
	t_lis* tmp;
	t_lis* prev;
	struct stat status;

	prev = NULL;
	tmp = info->names;
	while (tmp) {

		if (lstat(tmp->val, &status)) {
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd(tmp->val, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			// ft_printf("ls: %s: No such file or directory\n", tmp->val);
			tmp = tmp->next;
			ft_list_delete_element(&info, prev);
		} else {
			prev = tmp;
			tmp = tmp->next;
		}

		// DIR* dir = opendir(tmp->val);
		// if (dir == NULL) {
		// 	ft_printf("ls: cannot access \'%s\': No such file or directory\n", tmp->val);
		// 	tmp = tmp->next;
		// 	ft_list_delete_element(&info, prev);
		// } else {
		// 	prev = tmp;
		// 	tmp = tmp->next;
		// }
		// closedir(dir);
	}
}
