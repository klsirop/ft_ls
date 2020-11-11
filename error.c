#include "ft_ls.h"

void ft_wrong_flag(char wrong_flag) {
	ft_printf("ls: invalid option -- \'%c\'\n", wrong_flag);
	exit(1);
}
