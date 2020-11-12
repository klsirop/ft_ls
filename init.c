#include "ft_ls.h"

void	ft_init_info(t_info **info) {
	*info = (t_info *)malloc(sizeof(t_info));
	(*info)->flags = NULL;
	(*info)->names = NULL;
	(*info)->dir_names = NULL;
	(*info)->file_names = NULL;
	(*info)->deleted_dir = 0;
}

void	ft_init_dir_info(t_dir_info** dir_info) {
	*dir_info = (t_dir_info *)malloc(sizeof(t_dir_info));
	(*dir_info)->names = NULL;
	(*dir_info)->sort_order = 0;
	(*dir_info)->info_type = 0;
	(*dir_info)->is_Rec = -1;
	(*dir_info)->is_Hidden = -1;
}

void	ft_init_file_info(t_file_info **file_info) {
	(*file_info) = (t_file_info *)malloc(sizeof(t_file_info));
	(*file_info)->rights = NULL;
	(*file_info)->usr_name = NULL;
	(*file_info)->grp_name = NULL;
	(*file_info)->time = NULL;
	(*file_info)->link_name = NULL;
	(*file_info)->file_name = NULL;
	(*file_info)->next = NULL;
	(*file_info)->total = 0;
}
