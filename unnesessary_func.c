#include "ft_ls.h"

void	ft_print_flags(t_info *info) {
	ft_printf("flags: %s\n", info->flags);
}

void	ft_print_input_names(t_info *info) {
	t_lis *tmp;

	tmp = info->names;
	while (tmp) {
		ft_printf("%s ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_print_sort_order(t_dir_info *dir_info) {
	enum e_order_type order_type;

	order_type = dir_info->sort_order;
	ft_printf("order type: ");
	if (order_type == ALPH)
		ft_printf("ALPH\n");
	if (order_type == RALPH)
		ft_printf("RALPH\n");
	if (order_type == ORGN)
		ft_printf("ORGN\n");
	if (order_type == TMOD)
		ft_printf("TMOD\n");
	if (order_type == RTMOD)
		ft_printf("RTMOD\n");
	if (order_type == SIZE)
		ft_printf("SIZE\n");
	if (order_type == RSIZE)
		ft_printf("RSIZE\n");
}

void ft_print_info_type(t_dir_info *dir_info) {
	enum e_info_type info_type;

	info_type = dir_info->info_type;
	ft_printf("info type: ");
	if (info_type == L)
		ft_printf("%s\n", "L");
	else if (info_type == LO)
		ft_printf("%s\n", "LO");
	else if (info_type == LG)
		ft_printf("%s\n", "LG");
	else if (info_type == LOG)
		ft_printf("%s\n", "LOG");
	else if (info_type == U)
		ft_printf("%s\n", "U");
}

void	ft_print_is_r(t_dir_info *dir_info) {
	if (dir_info->is_rec == 0)
		ft_printf("is R: no\n");
	else
		ft_printf("is R: yes\n");
}

void	ft_print_is_hidden(t_dir_info *dir_info) {
	if (dir_info->is_hidden == 0)
		ft_printf("is hidden: no\n");
	else
		ft_printf("is hidden: yes\n");
}
