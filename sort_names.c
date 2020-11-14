#include "ft_ls.h"

void	ft_swap_list_elements(t_lis *here, t_lis *nex) {
	char *tmp;

	tmp = ft_strdup(here->val);
	ft_strdel(&(here->val));
	here->val = ft_strdup(nex->val);
	ft_strdel(&(nex->val));
	nex->val = ft_strdup(tmp);
	ft_strdel(&tmp);
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
			return ft_is_right_order_by_alph(lhs->val, rhs->val, order_type);
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
	int is_end_sorting;

	if (sort_order == ORGN)
		return ;

	len = ft_find_list_len(names);
	i = 0;

	is_end_sorting = 0;
	while (i < len && !is_end_sorting) {
		is_end_sorting = 1;
		tmp = names;
		while (tmp) {
			if (tmp && tmp->next && !ft_is_right_order(parent_name, tmp, tmp->next, sort_order)) {
				is_end_sorting = 0;
				ft_swap_list_elements(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
		i++;
	}
}

