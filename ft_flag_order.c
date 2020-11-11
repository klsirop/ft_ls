#include "ft_ls.h"

int	ft_flag_order(char fflag, char sflag, char* flags) {
	int len;

	len = ft_strlen(flags) - 1;
	while (len >= 0) {
		if (flags[len] == fflag) {
			return 0;
		}
		if (flags[len] == sflag) {
			return 1;
		}
		len--;
	}
	return 1;
}
