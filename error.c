#include "ft_ls.h"

void ft_wrong_flag(char wrong_flag) {
	// ft_printf("/bin/ls: illegal option -- %c\n", wrong_flag);
	// ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	ft_putstr_fd("/bin/ls: illegal option -- ", 2);
	ft_putchar_fd(wrong_flag, 2);
	ft_putstr_fd("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", 2);
	exit(1);
}

void	ft_error_permission_denided(char *dir_name) {
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(dir_name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(1);
}
