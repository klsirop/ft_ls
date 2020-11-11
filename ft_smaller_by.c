#include "ft_ls.h"

int		ft_smaller_by(char *lhs, char *rhs, enum e_order_type order_type) {
	if (order_type == ORGN) {
		return 0;
	} else if (order_type == ALPH) {
		if (ft_strcmp(lhs, rhs) < 0)
			return 1;
		else
			return 0;
	} else if (order_type = RALPH) {
		if (ft_strcmp(lhs, rhs) > 0)
			return 1;
		else
			return 0;
	} else if (order_type = TCRT) {
		if (ft_strcmp(lhs, rhs) > 0)
			return 1;
		else
			return 0;
	}
}
