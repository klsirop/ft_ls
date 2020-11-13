#include "ft_ls.h"

void	ft_swap_list_elements(t_lis *here, t_lis *nex) {
	char *nex_val;
	char *here_val;

	nex_val = ft_strdup(nex->val);
	here_val = ft_strdup(here->val);
	ft_strdel(&(here->val));
	ft_strdel(&(nex->val));
	here->val = ft_strdup(nex_val);
	nex->val = ft_strdup(here_val);
	ft_strdel(&here_val);
	ft_strdel(&nex_val);
}

void	ft_delete_point(char **no_point, char *str) {
	int i;

	if (!ft_strcmp(".", str) || !ft_strcmp("..", str)) {
		(*no_point) = ft_strdup(str);
		return ;
	}

	(*no_point) = (char *)malloc(sizeof(char) * ft_strlen(str));
	i = 1;
	while (str[i] != '\0') {
		(*no_point)[i - 1] = str[i];
		i++;
	}
	(*no_point)[i] = '\0';
}

// int		ft_no_point_strcmp(char *lhs, char *rhs) {
// 	char *lhs_no_point;
// 	char *rhs_no_point;
// 	int res;

// 	lhs_no_point = NULL;
// 	rhs_no_point = NULL;

// 	lhs_no_point = ft_strdup(lhs);
// 	rhs_no_point = ft_strdup(rhs);
// 	res = ft_strcmp(lhs_no_point, rhs_no_point);

// 	ft_strdel(&lhs_no_point);
// 	ft_strdel(&rhs_no_point);

// 	return (res);
// }

int		ft_is_right_order_by_alph(char *lhs, char *rhs, enum e_order_type order_type) {
	if (order_type == ALPH || order_type == TMOD || order_type == SIZE) {
		if (ft_strcmp(lhs, rhs) > 0)
			return 0;
		else
			return 1;
	} else {
		if (ft_strcmp(lhs, rhs) < 0)
			return 0;
		else
			return 1;
	}
	return 0;
}

int		ft_is_right_order(char *parent_name, t_lis *lhs, t_lis *rhs, enum e_order_type order_type) {
	struct stat lhs_stat;
	struct stat rhs_stat;
	char *lhs_full;
	char *rhs_full;

	lhs_full = ft_get_next_dir_name(parent_name, lhs->val);
	rhs_full = ft_get_next_dir_name(parent_name, rhs->val);
	lstat(lhs_full, &lhs_stat);
	lstat(rhs_full, &rhs_stat);
	ft_strdel(&lhs_full);
	ft_strdel(&rhs_full);

	if (order_type == ORGN)
		return 1;
	if (order_type == ALPH) {
		return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
	} else if (order_type == RALPH) {
		return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
	} else if (order_type == TMOD) {
		if (lhs_stat.st_mtime > rhs_stat.st_mtime)
			return 1;
		else if (lhs_stat.st_mtime == rhs_stat.st_mtime)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else
			return 0;
	} else if (order_type == RTMOD) {
		if (lhs_stat.st_mtime < rhs_stat.st_mtime)
			return 1;
		else if (lhs_stat.st_mtime == rhs_stat.st_mtime)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);/////////////////////////////////////chage!!!!
		else
			return 0;
	} else if (order_type == SIZE) {
		if (lhs_stat.st_size > rhs_stat.st_size)
			return 1;
		else if (lhs_stat.st_size == rhs_stat.st_size)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else 
			return 0;
	} else if (order_type == RSIZE) {
		if (lhs_stat.st_size < rhs_stat.st_size)
			return 1;
		else if (lhs_stat.st_size == rhs_stat.st_size)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else
			return 0;
	}
	return 0;
}

void	ft_sort_by(char *parent_name, t_lis *names, enum e_order_type sort_order) {
	t_lis *tmp;
	int len;
	int i;

	len = ft_find_list_len(names);
	// ft_print_list(names);
	i = 0;

	while (i < len) {
		tmp = names;
		while (tmp) {
			if (tmp && tmp->next && !ft_is_right_order(parent_name, tmp, tmp->next, sort_order)) {
				ft_swap_list_elements(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
		i++;
	}
}

// void	ft_sort_names(t_lis **names, t_dir_info* dir_info) {
// 	// there is no parent dir
// 	// if (dir_info->sort_order == ALPH) {
// 	// 	return ;
// 	// } else if (dir_info->sort_order == ALPH) {
// 	// 	ft_sort_by_alph(*names);
// 	// } else if (dir_info->sort_order == RALPH) {
// 	// 	ft_sort_by_ralph(*names);
// 	// } else if (dir_info->sort_order == TOPN) {
// 	// 	ft_sort_by_topn(*names);
// 	// }
// }
