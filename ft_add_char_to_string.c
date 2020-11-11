#include "ft_ls.h"

void	ft_add_char_to_string(char** str, char c) {
	char* new_str;
	int i;

	if (!(*str)) {
		*str = (char *)malloc(sizeof(char) * 2);
		(*str)[0] = c;
		(*str)[1] = '\0';
		return ;
	}

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	i = 0;
	while ((*str)[i] != '\0') {
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	ft_strdel(str);
	*str = ft_strdup(new_str);
	ft_strdel(&new_str);
}
