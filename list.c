#include "ft_ls.h"

void ft_list_add(t_lis** head, char* str) {
	t_lis* tmp;

	tmp = *head;
	if (tmp == NULL) {
		tmp = (t_lis *)malloc(sizeof(t_lis));
		tmp->val = ft_strdup(str);
		tmp->next = NULL;
		*head = tmp;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = (t_lis *)malloc(sizeof(t_lis));
		tmp = tmp->next;
		tmp->val = ft_strdup(str);
		tmp->next = NULL;
	}
}

void ft_file_list_add(t_file_info** head, char *str) {
	t_file_info* tmp;

	tmp = *head;
	if (tmp == NULL) {
		// tmp = (t_file_info *)malloc(sizeof(t_file_info));
		ft_init_file_info(&tmp);
		tmp->file_name = ft_strdup(str);
		// tmp->next = NULL;
		*head = tmp;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		ft_init_file_info(&(tmp->next));
		// tmp->next = (t_file_info *)malloc(sizeof(t_file_info));
		tmp = tmp->next;
		tmp->file_name = ft_strdup(str);
		// tmp->next = NULL;
	}
}

void ft_file_list_add_l(t_file_info** head, t_file_info *new_el) {
	t_file_info* tmp;

	tmp = *head;
	if (tmp == NULL) {
		*head = new_el;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new_el;
	}
}

void	ft_list_delete_element(t_info** info, t_lis* prev) {
	t_lis* tmp;

	if (prev == NULL) {
		tmp = (*info)->names;
		(*info)->names = tmp->next;
		ft_strdel(&(tmp->val));
		free(tmp);
		return ;
	}
	tmp = prev->next;
	prev->next = tmp->next;
	ft_strdel(&(tmp->val));
	free(tmp);
}

int 	ft_find_list_len(t_lis *head) {
	t_lis *tmp;
	int len;

	len = 0;
	tmp = head;
	while (tmp) {
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_print_list(t_lis *head) {
	t_lis *tmp;

	tmp = head;
	while (tmp) {
		ft_printf("%s ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

// void	ft_find_place_in_list(t_lis **head, struct dirent* dirent, t_dir_info* dir_info) {
// 	t_lis *new_el;
// 	t_lis *tmp;

// 	new_el = (t_lis *)malloc(sizeof(t_lis));
// 	new_el->val = dirent->d_name;
// 	new_el->next = NULL;

// 	if (*head == NULL) {
// 		*head = new_el;
// 		return ;
// 	}

// 	if (ft_is_right_order(new_el->val, (*head)->val, dir_info->sort_order)) {
// 		new_el->next = *head;
// 		*head = new_el;
// 	}

// 	tmp = *head;
// 	while (tmp) {
// 		if (!ft_is_right_order())

// 		tmp = tmp->next;
// 	}
// }
