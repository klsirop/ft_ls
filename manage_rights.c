#include "ft_ls.h"

void	ft_get_file_type(mode_t mode, t_file_info* file_info) {
	mode = mode & S_IFMT;
	if (S_ISDIR(mode))
		file_info->rights->mode = 'd';
	else if (S_ISREG(mode))
		file_info->rights->mode = '-';
	else if (S_ISLNK(mode))
		file_info->rights->mode = 'l';
	else if (S_ISCHR(mode))
		file_info->rights->mode = 'c';
	else if (S_ISBLK(mode))
		file_info->rights->mode = 'b';
	else if (S_ISFIFO(mode))
		file_info->rights->mode = 'p';
	else if (S_ISSOCK(mode))
		file_info->rights->mode = 's';
	else
		file_info->rights->mode = '-';
}

void	ft_get_usr_rights(mode_t mode, t_file_info* file_info) {
	mode = mode & S_IRWXU;
	if (S_IRUSR & mode)
		file_info->rights->usr_rights[0] = 'r';
	else
		file_info->rights->usr_rights[0] = '-';
	if (S_IWUSR & mode)
		file_info->rights->usr_rights[1] = 'w';
	else
		file_info->rights->usr_rights[1] = '-';
	if (S_IXUSR & mode)
		file_info->rights->usr_rights[2] = 'x';
	else
		file_info->rights->usr_rights[2] = '-';
}

void	ft_get_group_rights(mode_t mode, t_file_info* file_info) {
	mode = mode & S_IRWXG;
	if (S_IRGRP & mode)
		file_info->rights->grp_rights[0] = 'r';
	else
		file_info->rights->grp_rights[0] = '-';
	if (S_IWGRP & mode)
		file_info->rights->grp_rights[1] = 'w';
	else
		file_info->rights->grp_rights[1] = '-';
	if (S_IXGRP & mode)
		file_info->rights->grp_rights[2] = 'x';
	else
		file_info->rights->grp_rights[2] = '-';
}

void	ft_get_other_rights(mode_t mode, t_file_info* file_info) {
	mode = mode & S_IRWXO;
	if (S_IROTH & mode)
		file_info->rights->oth_rights[0] = 'r';
	else
		file_info->rights->oth_rights[0] = '-';
	if (S_IWOTH & mode)
		file_info->rights->oth_rights[1] = 'w';
	else
		file_info->rights->oth_rights[1] = '-';
	if (S_IXOTH & mode)
		file_info->rights->oth_rights[2] = 'x';
	else
		file_info->rights->oth_rights[2] = '-';
}

void	ft_get_spec_rights(mode_t mode, t_file_info* file_info) {
	if (S_ISUID & mode) {
		if (file_info->rights->usr_rights[2] == '-')
			file_info->rights->usr_rights[2] = 'S';
		else
			file_info->rights->usr_rights[2] = 's';
	}

	if (S_ISGID & mode) {
		if (file_info->rights->grp_rights[2] == '-')
			file_info->rights->grp_rights[2] = 'S';
		else
			file_info->rights->grp_rights[2] = 's';
	}

	if (S_ISVTX & mode) {
		if (file_info->rights->oth_rights[2] == '-')
			file_info->rights->oth_rights[2] = 'T';
		else
			file_info->rights->oth_rights[2] = 't';
	}
}

void	ft_get_file_acl(char *path_to_file, t_file_info* file_info) {
	char	buf[101];

	if (listxattr(path_to_file, buf, sizeof(buf), 0) > 0)
		file_info->rights->acl = '@';
	file_info->rights->acl = ' ';
}

void	ft_print_rights(struct stat status, char *path_to_file, t_file_info* file_info) {
	mode_t mode;

	ft_init_t_rights(&(file_info->rights));
	mode = status.st_mode;

	ft_get_file_type(mode, file_info);
	ft_get_usr_rights(mode, file_info);
	ft_get_group_rights(mode, file_info);
	ft_get_other_rights(mode, file_info);
	ft_get_spec_rights(mode, file_info);
	ft_get_file_acl(path_to_file, file_info);
}