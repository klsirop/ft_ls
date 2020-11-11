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

int		ft_no_point_strcmp(char *lhs, char *rhs) {
	char *lhs_no_point;
	char *rhs_no_point;
	int res;

	lhs_no_point = NULL;
	rhs_no_point = NULL;

	if ((lhs)[0] == '.')
		ft_delete_point(&lhs_no_point, lhs);
	else
		lhs_no_point = ft_strdup(lhs);

	if ((rhs)[0] == '.')
		ft_delete_point(&rhs_no_point, rhs);
	else
		rhs_no_point = ft_strdup(rhs);

	// ft_printf("before: %s after: %s\n", lhs, lhs_no_point);
	// ft_printf("before: %s after: %s\n", rhs, rhs_no_point);

	res = ft_strcmp(lhs_no_point, rhs_no_point);

	ft_strdel(&lhs_no_point);
	ft_strdel(&rhs_no_point);

	return (res);
}

int		ft_is_right_order_by_alph(char *lhs, char *rhs, enum e_order_type order_type) {
	if (order_type == ALPH) {
		if (ft_no_point_strcmp(lhs, rhs) > 0)
			return 1;
		else
			return 0;
	} else if (order_type == RALPH) {
		if (ft_no_point_strcmp(lhs, rhs) < 0)
			return 1;
		else
			return 0;
	}
}

int		ft_is_right_order(t_lis *lhs, t_lis *rhs, enum e_order_type order_type) {
	struct stat lhs_stat;
	struct stat rhs_stat;


	stat(lhs->val, &lhs_stat);
	stat(rhs->val, &rhs_stat);

	if (order_type == ALPH) {
		if (ft_no_point_strcmp(lhs->val, rhs->val) > 0)
			return 1;
		else
			return 0;
	} else if (order_type == RALPH) {
		if (ft_no_point_strcmp(lhs->val, rhs->val) < 0)
			return 1;
		else
			return 0;
	} else if (order_type == TACC) {
		// ft_printf("%s %ld %s %ld\n", lhs->val, lhs_stat.st_atime, rhs->val, rhs_stat.st_atime);
		if (lhs_stat.st_atime < rhs_stat.st_atime)
			return 1;
		else if (lhs_stat.st_atime == rhs_stat.st_atime)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else
			return 0;
	} else if (order_type == RTACC) {
		if (lhs_stat.st_atime >= rhs_stat.st_atime)
			return 1;
		else if (lhs_stat.st_atime == rhs_stat.st_atime)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else
			return 0;
	} else if (order_type == TMOD) {
		// ft_printf("%s %ld %s %ld\n", lhs->val, lhs_stat.st_mtime, rhs->val, rhs_stat.st_mtime);
		if (lhs_stat.st_mtime < rhs_stat.st_mtime)
			return 1;
		else if (lhs_stat.st_mtime == rhs_stat.st_mtime)
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		else
			return 0;
	} else if (order_type == RTMOD) {
		if (lhs_stat.st_mtime >= rhs_stat.st_mtime)
			return 1;
		else if (lhs_stat.st_mtime == rhs_stat.st_mtime) {
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
		}
		else
			return 0;
	}
	return 0;
}

void	ft_sort_by(t_lis *names, t_dir_info* dir_info) {
	t_lis *tmp;
	int len;
	int i;

	len = ft_find_list_len(names);
	i = 0;

	while (i < len) {
		tmp = names;
		while (tmp) {
			if (tmp && tmp->next && ft_is_right_order(tmp, tmp->next, dir_info->sort_order)) {
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
