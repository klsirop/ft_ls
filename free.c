#include "ft_ls.h"

void	ft_free_t_rights(t_rights **rights) {
	ft_strdel(&(*rights)->usr_rights);
	ft_strdel(&(*rights)->grp_rights);
	ft_strdel(&(*rights)->oth_rights);
	free(*rights);
	*rights = NULL;
}

void	ft_free_t_dtime(t_dtime **time) {
	ft_strdel(&((*time)->month));
	ft_strdel(&((*time)->day));
	ft_strdel(&((*time)->hour));
	ft_strdel(&((*time)->min));
	free(*time);
	*time = NULL;
}

void	ft_free_t_file_info(t_file_info **head) {
	t_file_info *tmp;

	while (*head) {
		tmp = *head;
		*head = (*head)->next;

		if (tmp->rights) {
			ft_free_t_rights(&(tmp->rights));
		}
		if (tmp->usr_name) {
			ft_strdel(&(tmp->usr_name));
		}
		if (tmp->grp_name) {
			ft_strdel(&(tmp->grp_name));
		}
		if (tmp->time) {
			ft_free_t_dtime(&(tmp->time));
		}
		if (tmp->link_name) {
			ft_strdel(&(tmp->link_name));
		}
		if (tmp->file_name) {
			ft_strdel(&(tmp->file_name));
		}

		free (tmp);
		tmp = NULL;
	}
}

void	ft_free_info(t_info **info) {
	if ((*info)->flags)
		ft_strdel(&((*info)->flags));
	if ((*info)->names)
		ft_delete_list(&((*info)->names));
	if ((*info)->file_names)
		ft_delete_list(&((*info)->file_names));
	if ((*info)->dir_names)
		ft_delete_list(&((*info)->dir_names));
	free(*info);
	*info = NULL;
}
