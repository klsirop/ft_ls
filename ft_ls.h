/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:50:17 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/21 14:52:37 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# ifndef DIRENT_H
#  define DIRENT_H
#  include <dirent.h>
# endif
# ifndef SYS_STAT_H
#  define SYS_STAT_H
#  include <sys/stat.h>
# endif
# ifndef PWD_H
#  define PWD_H
#  include <pwd.h>
# endif
# ifndef GRP_H
#  define GRP_H
#  include <grp.h>
# endif
# ifndef SYS_XATTR_H
#  define SYS_XATTR_H
#  include <sys/xattr.h>
# endif
# ifndef LIBFT_H
#  define LINFT_H
#  include "./libft/includes/libft.h"
# endif

#include <sys/acl.h>

enum	e_order_type {
	ORGN,
	ALPH,
	RALPH,
	TMOD,
	RTMOD,
	SIZE,
	RSIZE,
	TBITRH,
	RTBIRTH
};

enum	e_info_type {
	L,
	LG,
	LO,
	LOG,
	U
};

typedef struct		s_lis {
	char			*val;
	struct s_lis	*next;
}					t_lis;

typedef struct	s_info {
	char		*flags;
	t_lis		*names;
	t_lis		*file_names;
	t_lis		*dir_names;
	int			deleted_dir;
}				t_info;

typedef struct			s_dir_info {
	t_lis				*names;
	enum e_order_type	sort_order;
	enum e_info_type	info_type;
	int					is_rec;
	int					is_hidden;
	int					is_birth_time;
}						t_dir_info;

typedef struct	s_rights {
	char		mode;
	char		*usr_rights;
	char		*grp_rights;
	char		*oth_rights;
	char		acl;
}				t_rights;

typedef struct	s_dtime
{
	char		*month;
	char		*day;
	char		*hour;
	char		*min;
	char		*year;
}				t_dtime;

typedef struct			s_file_info {
	t_rights			*rights;
	nlink_t				hard_links;
	char				*usr_name;
	char				*grp_name;
	off_t				file_size;
	t_dtime				*time;
	t_dtime				*time_birth;
	char				*link_name;
	char				*file_name;
	int					total;
	int					major;
	int					minor;
	int					is_device;
	struct s_file_info	*next;
}						t_file_info;

typedef struct 			s_tree
{
		t_file_info		*field;
		struct s_tree	*left;
		struct s_tree	*right;
}						t_tree;


typedef struct	s_field_width
{
	int			hard_links;
	int			user;
	int			group;
	int			size;
	int			mounth;
	int			day;
	int			mounth_birth;
	int			day_birth;
	int			filename;
	int			linkname;
	int			time;
	int			time_birth;
	int			major;
	int			minor;
}				t_field_width;

/*
** init.c
*/

void	ft_init_info(t_info **info);
void	ft_init_dir_info(t_dir_info **dir_info);
void	ft_init_file_info(t_file_info **file_info);
void	ft_init_t_rights(t_rights **rights);
void	ft_init_t_dtime(t_dtime **time);


/*
** init_structs.c
*/

void	ft_init_width_info(t_field_width *width_info);
void	ft_init_t_tree(t_tree **head);

/*
** parse_input.c
*/

void	ft_parse_input(int argc, char **argv, t_info *info);

/*
** error.c
*/

void	ft_wrong_flag(char wrong_flag);
void	ft_error_permission_denided(char *dir_name);
void	ft_malloc_error();
void	ft_lstat_error(void);

/*
** list.c
*/

void	ft_list_delete_element(t_info **info, t_lis *prev);
int		ft_find_list_len(t_lis *head);
void	ft_print_list(t_lis *head);
void	ft_delete_list(t_lis **head);
int		ft_find_list_len_file_info(t_file_info *head);

/*
** ft_reverse_list.c
*/

void	ft_reverse_list(t_lis **head);
void	ft_reverse_list_file_info(t_file_info **head);

/*
** list_add.c
*/

void	ft_list_add_begin(t_lis **head, char *str);
void	ft_list_add(t_lis **head, char *str);
void	ft_file_list_add_l(t_file_info **head, t_file_info *new_el);
void	ft_list_add_l_begin(t_file_info **head, t_file_info *new_el);
void	ft_file_list_add_begin(t_file_info **head, char *str);

/*
** ft_add_char_to_string.c
*/

void	ft_add_char_to_string(char **str, char c);

/*
** unnesessary_func.c
*/

void	ft_print_flags(t_info *info);
void	ft_print_input_names(t_info *info);
void	ft_print_sort_order(t_dir_info *dir_info);
void	ft_print_info_type(t_dir_info *dir_info);
void	ft_print_is_r(t_dir_info *dir_info);
void	ft_print_is_hidden(t_dir_info *dir_info);

/*
** ft_is_right_dir_names.c
*/

void	ft_is_right_dir_names(t_info *info);

/*
** ft_find_sort_order.c
*/

void	ft_find_sort_order(t_dir_info *dir_info, t_info *info);

/*
** ft_find_info_type.c
*/

void	ft_find_info_type(t_dir_info *dir_info, t_info *info);
void	ft_find_is_r(t_dir_info *dir_info, t_info *info);
void	ft_find_is_hidden(t_dir_info *dir_info, t_info *info);

/*
** sort.c
*/

void	ft_sort_names(t_lis **names, t_dir_info *dir_info);

/*
** sort_names.c
*/

void	ft_sort_by(char *parent_name, t_lis **names, enum e_order_type sort_order);
int		ft_is_right_order_by_alph(char *lhs, char *rhs, enum e_order_type order_type);
void	ft_sort_by_file_info(char *parent_name, t_file_info **file_info, enum e_order_type sort_order);

/*
** out_dir.c
*/

int		ft_insert_all_dir_names(char *name, t_lis **head, t_dir_info *dir_info, int is_only_dirs);
int	ft_insert_all_dir_names_rec(char *name, t_lis **head, t_dir_info* dir_info, int is_only_dirs);
t_tree	*ft_out_dir(char* name, t_dir_info* dir_info, t_field_width **width_info);

/*
** print_dir.c
*/

int	ft_max(int a, int b);
void	ft_print_dir(t_dir_info *dir_info, t_file_info *file_info, int is_dir);
void	ft_print_node(t_file_info *tmp, t_dir_info *dir_info, t_field_width *width_info, int is_device);

/*
** free.c
*/

void	ft_free_t_file_info(t_file_info **head);
void	ft_free_t_info(t_info **info);
void	ft_free_t_dir_info(t_dir_info **dir_info);

/*
** print_like_l.c
*/

int		ft_print_like_l(char *parent_dir, char *dir_name, t_file_info *file_info);
char	*ft_strconcat(char *s1, char *s2);

/*
** separate_files_and_dirs.c
*/

void	ft_separate_files_and_dirs(t_info *info, t_dir_info *dir_info);
int		ft_is_dir(char *name, t_dir_info *dir_info);

/*
** main.c
*/

char	*ft_get_next_dir_name(char *start, char *end);

/*
** manage_flags_overlap.c
*/

void	ft_manage_flags_overlap(t_info *info);

/*
** manage_rights.c
*/

void	ft_print_rights(struct stat status, char *path_to_file, t_file_info *file_info);

/*
** manage_file_time.c
*/

void	ft_print_time_modify(struct stat status, t_file_info *file_info);
void	ft_print_time_birth(struct stat status, t_file_info *file_info);
void	ft_free_after_split(char **arr);

/*
** ft_find_time_or_year.c
*/

void	ft_find_year_or_time_birth(char **separate_date,
								char **separate_time,
								t_file_info *file_info,
								time_t bitime);
void	ft_find_year_or_time(char **separate_date,
								char **separate_time,
								t_file_info *file_info,
								time_t mtime);


/*
** ft_find_all_width.c
*/

void	ft_find_all_width(t_file_info *file_info, t_field_width **width_info);
void	ft_find_all_width_tree(t_tree *tree, t_field_width **width_info);
void	ft_find_first_width(
								t_field_width **width_info,
								t_file_info *tmp);
void	ft_find_last_width(
								t_field_width **width_info,
								t_file_info *tmp);

/*
** ft_find_field_width.c
*/

void	ft_find_device_width(
								t_field_width **width_info,
								t_file_info *tmp);
void	ft_find_time_width(
								t_field_width **width_info,
								t_file_info *tmp);

/*
** manage_access_rights.c
*/

void	ft_get_usr_rights(mode_t mode, t_file_info *file_info);
void	ft_get_group_rights(mode_t mode, t_file_info *file_info);
void	ft_get_other_rights(mode_t mode, t_file_info *file_info);

/*
** ft_is_right_order.c
*/

int		ft_is_right_order(char *parent_name, char *lhs, char *rhs, enum e_order_type order_type);

/*
** tree.c
*/

void	ft_print_dir_tree(t_tree *head, t_dir_info *dir_info, t_field_width *width_info, int is_device);
void ft_free_t_tree(t_tree *head);
t_tree	*ft_insert_tree_element(t_tree *head, t_file_info *new, char *parent_name, enum e_order_type order_type);
void	ft_just_print_tree(t_tree *head);

/*
** ft_is_right_order_by.c
*/

int		ft_is_right_order_tmod(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs);
int		ft_is_right_order_tbirth(struct stat lhs_stat,
	struct stat rhs_stat,
	char *lhs,
	char *rhs);
int		ft_is_right_order_rtmod(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs);
int		ft_is_right_order_rtbirth(struct stat lhs_stat,
								struct stat rhs_stat,
								char *lhs,
								char *rhs);

void	ft_print_list_t_info(t_file_info *head);

/*
** ft_do_papka.c
*/

void	ft_do_papka(char *dir_name, t_dir_info *dir_info);

/*
** ft_out_files.c
*/

void	ft_out_files(t_info *info, t_dir_info *dir_info);

/*
** ft_insert_all_dir_names.c
*/

int	ft_insert_all_dir_names_rec(char *name,
								t_lis **head,
								t_dir_info *dir_info,
								int is_only_dirs);

/*
** get_file_info.c
*/

void	ft_print_size(struct stat *status, t_file_info *file_info);
void	ft_print_hard_links(struct stat status, t_file_info *file_info);
void	ft_print_user_name(struct stat status, t_file_info *file_info);
void	ft_print_group_name(struct stat status, t_file_info *file_info);

/*
** ft_output_l.c
*/

void	ft_output_l(t_dir_info *dir_info, t_file_info *file_info, int is_dir);
void	ft_output_l_four_col(t_dir_info *dir_info,
							t_file_info *tmp,
							t_field_width *width_info);
void	ft_output_l_time(t_dir_info *dir_info,
						t_field_width *width_info,
						t_file_info *tmp);

#endif
