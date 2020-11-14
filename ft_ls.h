
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

#include <sys/stat.h>
#include <unistd.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <sys/xattr.h>

#include <sys/types.h>

#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include "./libft/includes/get_next_line.h"

enum e_order_type {
	ORGN,
	ALPH,
	RALPH,
	TMOD,
	RTMOD,
	// TACC,
	// RTACC,
	SIZE,
	RSIZE
};

enum e_info_type {
	L, // list (-l)
	LG, // list(!) no user (-g)
	LO, // list(!) no group (-o)
	LOG, // list no group no user
	U // usual
	
	//U, // no sort (-U)
	//F, // no sort with .files (-f)
	// LU,
	// G,
};

typedef struct	s_lis {
	char*			val;
	struct s_lis	*next;
}				t_lis;

typedef struct	s_info {
	char*		flags;
	t_lis*		names;
	t_lis*		file_names;
	t_lis*		dir_names;
	int			deleted_dir;
}				t_info;

typedef struct	s_dir_info {
	t_lis* names;
	enum e_order_type sort_order;
	enum e_info_type info_type;
	int	is_Rec;
	int is_Hidden;
}				t_dir_info;

typedef struct	s_rights {
	char	mode;
	char *usr_rights;
	char *grp_rights;
	char *oth_rights;
	char acl;
}				t_rights;

typedef struct s_dtime
{
	char *month;
	char *day;
	char *hour;
	char *min;
	char *year;
}				t_dtime;


typedef struct	s_file_info {
	t_rights *rights;
	nlink_t	hard_links;
	char *usr_name;
	char *grp_name;
	off_t file_size;
	t_dtime *time;
	char *link_name;
	char *file_name;
	int total;
	struct s_file_info *next;
}				t_file_info;

typedef struct s_field_width
{
	int	hard_links;
	int user;
	int group;
	int size;
	int mounth;
	int day;
	int filename;
	int linkname;
	int time;
}				t_field_width;


/*
** init.c
*/

void	ft_init_info(t_info **info);
void	ft_init_dir_info(t_dir_info** dir_info);
void	ft_init_file_info(t_file_info **file_info);
void	ft_init_t_rights(t_rights **rights);
void	ft_init_t_dtime(t_dtime **time);

/*
** parse_input.c
*/

void ft_parse_input(int argc, char **argv, t_info* info);

/*
** error.c
*/

void ft_wrong_flag(char wrong_flag);
void	ft_error_permission_denided(char *dir_name);

/*
** list.c
*/

void ft_list_add(t_lis** head, char* str);
void	ft_list_delete_element(t_info** info, t_lis* prev);
int 	ft_find_list_len(t_lis *head);
void ft_file_list_add(t_file_info** head, char *str);
void ft_file_list_add_l(t_file_info** head, t_file_info *new_el);
void	ft_print_list(t_lis *head);
void	ft_delete_list(t_lis **head);

/*
** ft_add_char_to_string.c
*/

void	ft_add_char_to_string(char** str, char c);

/*
** unnesessary_func.c
*/

void	ft_print_flags(t_info *info);
void	ft_print_input_names(t_info *info);
void	ft_print_sort_order(t_dir_info *dir_info);
void ft_print_info_type(t_dir_info *dir_info);
void	ft_print_is_R(t_dir_info *dir_info);
void	ft_print_is_hidden(t_dir_info *dir_info);

/*
** ft_is_right_dir_names.c
*/

void	ft_is_right_dir_names(t_info* info);

/*
** ft_find_sort_order.c
*/

void	ft_find_sort_order(t_dir_info* dir_info, t_info* info);

/*
** ft_flag_order.c
*/

int	ft_flag_order(char fflag, char sflag, char* flags);

/*
** ft_find_info_type.c
*/

void	ft_find_info_type(t_dir_info* dir_info, t_info* info);
void	ft_find_is_R(t_dir_info* dir_info, t_info* info);
void	ft_find_is_hidden(t_dir_info* dir_info, t_info* info);

/*
** sort.c
*/

void	ft_sort_names(t_lis **names, t_dir_info* dir_info);

/*
** sort_names.c
*/

void	ft_sort_by(char *parent_name, t_lis *names, enum e_order_type sort_order);
int		ft_is_right_order(char *parent_name, t_lis *lhs, t_lis *rhs, enum e_order_type order_type);

/*
** out_dir.c
*/

void	ft_out_dir(char* name, t_dir_info* dir_info, t_file_info **file_info);
int	ft_insert_all_dir_names(char *name, t_lis **head, t_dir_info* dir_info, int is_only_dirs);


/*
** print_dir.c
*/

void	ft_print_dir(t_dir_info* dir_info, t_file_info *file_info, int is_dir);

/*
** free.c
*/

void	ft_free_t_file_info(t_file_info **head);
void	ft_free_t_info(t_info **info);
void	ft_free_t_dir_info(t_dir_info **dir_info);

/*
** print_like_l.c
*/

int	ft_print_like_l(char *parent_dir, char *dir_name, t_dir_info* dir_info, t_file_info *file_info);
char *ft_strconcat(char *s1, char *s2);

/*
** separate_files_and_dirs.c
*/

void	ft_separate_files_and_dirs(t_info *info);
int	ft_is_dir(char *name);

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

void	ft_print_rights(struct stat status, char *path_to_file, t_file_info* file_info);

/*
** manage_file_time.c
*/

void	ft_print_time_modify(struct stat status, t_file_info* file_info);

/*
** ft_find_all_width.c
*/

void	ft_find_all_width(t_file_info *file_info, t_field_width **width_info);