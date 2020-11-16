#include "ft_ls.h"

char *ft_strconcat(char *s1, char *s2) {
	int len1;
	int len2;
	int i;
	int j;
	char *res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	i = 0;
	while (i < len1) {
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2) {
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return res;
}

void	ft_print_size(struct stat *status, t_file_info *file_info) {
	if (file_info->rights->mode == 'c')
		return ;
	off_t size = status->st_size;
	file_info->file_size = size;
}

void	ft_print_hard_links(struct stat status, t_file_info *file_info) {
	nlink_t nlinks;

	nlinks = status.st_nlink;
	file_info->hard_links = nlinks;
}

void	ft_print_user_name(struct stat status, t_file_info *file_info) {
	uid_t st_uid;
	struct passwd *pass;

	st_uid = status.st_uid;
	pass = getpwuid(st_uid);
	file_info->usr_name = ft_strdup(pass->pw_name);
}

void	ft_print_group_name(struct stat status, t_file_info *file_info) {
	gid_t st_gid;
	struct group *gr;

	st_gid = status.st_gid;
	gr = getgrgid(st_gid);
	file_info->grp_name = ft_strdup(gr->gr_name);
}

void	ft_print_link(char *path_to_file, t_file_info *file_info) {
	char buf[256];

	ft_memset(buf, '\0', 256);
	readlink(path_to_file, buf, 255);
	file_info->link_name = ft_strdup(buf);
}

void	ft_get_deivce_num(struct stat status, t_file_info *file_info, t_dir_info* dir_info)
{
	dev_t dev;

	if (file_info->rights->mode != 'c' && file_info->rights->mode != 'b')
		return ;
	dev = status.st_rdev;
	file_info->major = major(dev);
	file_info->minor = minor(dev);
	file_info->is_device = 1;
}

int	ft_print_like_l(char *parent_dir, char *dir_name, t_dir_info* dir_info, t_file_info *file_info) {
	struct stat status;
	char *path_to_file;
	char *tmp;

	if (parent_dir) {
		tmp = ft_strconcat(parent_dir, "/");
		path_to_file = ft_strconcat(tmp, dir_name);
		ft_strdel(&tmp);
	} else {
		path_to_file = ft_strdup(dir_name);
	}
	lstat(path_to_file, &status);
	ft_print_rights(status, path_to_file, file_info);
	ft_print_hard_links(status, file_info);
	ft_print_user_name(status, file_info);
	ft_print_group_name(status, file_info);
	ft_get_deivce_num(status, file_info, dir_info);
	ft_print_size(&status, file_info);
	ft_print_time_modify(status, file_info);
	file_info->file_name = ft_strdup(dir_name);
	if (file_info->rights->mode == 'l')
		ft_print_link(path_to_file, file_info);
	ft_strdel(&path_to_file);
	return status.st_blocks;
}
