#include "ft_ls.h"

void ft_wrong_flag(char wrong_flag) {
	ft_putstr_fd("/bin/ls: illegal option -- ", 2);
	ft_putchar_fd(wrong_flag, 2);
	ft_putstr_fd("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", 2);
	exit(1);
}

char	*ft_cut_path(char *path) {
	char *name;
	int last_slash;
	int i;

	last_slash = 0;
	i = 0;
	while (path && path[i] != '\0') {
		if (path[i] == '/')
			last_slash = i;
		i++;
	}
	if (last_slash != 0)
		last_slash++;

	name = ft_strsub(path, last_slash, ft_strlen(path) - last_slash);
	return name;
}

void	ft_error_permission_denided(char *dir_name) {
	char *only_name;

	only_name = ft_cut_path(dir_name);
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(only_name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	ft_strdel(&only_name);
	// exit(1);
}
