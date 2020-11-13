#include "ft_ls.h"

// void	ft_print_rights(struct dirent* dirent) {
// }

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

void ft_free_after_split(char **arr) {
	int i;

	i = 0;
	while (arr[i]) {
		ft_strdel(&arr[i]);
		i++;
	}
}

void	ft_print_size(struct stat *status, t_file_info *file_info) {
	off_t size = status->st_size; //long int ?
	file_info->file_size = size;
	// ft_printf("size: %lld\n", status->st_size);
}

void	ft_print_hard_links(struct stat status, t_file_info *file_info) {
	nlink_t nlinks; //unsigned long int

	nlinks = status.st_nlink;
	file_info->hard_links = nlinks;
}

void	ft_print_user_name(struct stat status, t_file_info *file_info) {
	uid_t st_uid; //unsigned int
	struct passwd *pass;

	st_uid = status.st_uid;
	pass = getpwuid(st_uid);
	file_info->usr_name = ft_strdup(pass->pw_name);
}

void	ft_print_group_name(struct stat status, t_file_info *file_info) {
	gid_t st_gid; //unsigned int
	struct group *gr;

	st_gid = status.st_gid;
	gr = getgrgid(st_gid);
	file_info->grp_name = ft_strdup(gr->gr_name);
}

void ft_print_time_modify(struct stat status, t_file_info* file_info) {
	time_t mtime; //long int
	char *full_time;
	char **separate_date;
	char **separate_time;
	struct timespec mtimespec;
	time_t now_time;
	char *now_time_str;
	char *now_year;
	char **separate_now_time;
	char *file_year;

	mtime = status.st_mtime;
	// mtimespec = status.st_mtimespec;
	// ft_printf("%d\n", mtimespec.tv_nsec);
	// ft_printf("%d\n", mtime);
	full_time = ft_strdup(ctime(&mtime));
	separate_date = ft_strsplit(full_time, ' ');
	separate_time = ft_strsplit(separate_date[3], ':');

	file_info->time = (t_dtime *)malloc(sizeof(t_dtime));

	file_info->time->month = ft_strdup(separate_date[1]);
	file_info->time->day = ft_strdup(separate_date[2]);

	file_info->time->hour = NULL;
	file_info->time->min = NULL;
	file_info->time->year = NULL;
	now_time = time(&now_time);
	now_time_str = ft_strdup(ctime(&now_time));
	separate_now_time = ft_strsplit(now_time_str, ' ');
	now_year = ft_strsub(separate_now_time[4], 0, 4);
	file_year = ft_strsub(separate_date[4], 0, ft_strlen(separate_date[4]) - 1);
	// ft_printf("%s", file_year);

	if (!ft_strcmp(now_year, file_year)) {
		file_info->time->hour = ft_strdup(separate_time[0]);
		file_info->time->min = ft_strdup(separate_time[1]);
	} else {
		file_info->time->year = ft_strdup(file_year);
	}


	ft_free_after_split(separate_time);
	ft_free_after_split(separate_date);
	free(separate_time);
	free(separate_date);
	ft_strdel(&full_time);
}

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

	file_info->rights = (t_rights *)malloc(sizeof(t_rights));
	file_info->rights->usr_rights = (char *)malloc(sizeof(char) * 4);
	file_info->rights->grp_rights = (char *)malloc(sizeof(char) * 4);
	file_info->rights->oth_rights = (char *)malloc(sizeof(char) * 4);
	file_info->rights->usr_rights[3] = '\0';
	file_info->rights->grp_rights[3] = '\0';
	file_info->rights->oth_rights[3] = '\0';

	mode = status.st_mode;

	ft_get_file_type(mode, file_info);
	ft_get_usr_rights(mode, file_info);
	ft_get_group_rights(mode, file_info);
	ft_get_other_rights(mode, file_info);
	ft_get_spec_rights(mode, file_info);
	ft_get_file_acl(path_to_file, file_info);
}

void	ft_print_link(struct stat status, char *path_to_file, t_file_info *file_info) {
	char buf[256];

	status = status;

	ft_memset(buf, '\0', 256);
	readlink(path_to_file, buf, 255);
	file_info->link_name = ft_strdup(buf);
}

int	ft_print_like_l(char *parent_dir, char *dir_name, t_dir_info* dir_info, t_file_info *file_info) {
	struct stat status;
	char *path_to_file;
	char *tmp;

	// ft_printf("name: %s", dir_name);
	if (parent_dir) {
		char *hash = ft_strdup("/");
		tmp = ft_strconcat(parent_dir, hash);
		path_to_file = ft_strconcat(tmp, dir_name);
		ft_strdel(&tmp);
	} else {
		path_to_file = ft_strdup(dir_name);
	}
	lstat(path_to_file, &status);
	// blkcnt_t blocks; //long int

	// blocks = status.st_blocks;
	// ft_printf(":%s\n", path_to_file);
	// file_info->total += status.st_blocks;
	// ft_printf("bblocks: %d\n", status.st_blocks);

	ft_print_rights(status, path_to_file, file_info);
	ft_print_hard_links(status, file_info);
	ft_print_user_name(status, file_info);
	ft_print_group_name(status, file_info);
	ft_print_size(&status, file_info);
	ft_print_time_modify(status, file_info);
	file_info->file_name = ft_strdup(dir_name);
	if (file_info->rights->mode == 'l')
		ft_print_link(status, path_to_file, file_info);
	ft_strdel(&path_to_file);
	return status.st_blocks;
	// return 0;
}
