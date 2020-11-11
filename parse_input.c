#include "ft_ls.h"

void ft_parse_flag(char* word, char** flags) {
	char* known_flags;
	int i;

	i = 1;
	known_flags = ft_strdup("lRartufUgG");
	while (word[i] != '\0') {
		if (!ft_strchr(known_flags, word[i])) {
			ft_wrong_flag(word[i]);
		}
		else {
			if (!(*flags) || !ft_strchr(*flags, word[i])) {
				ft_add_char_to_string(flags, word[i]);
			}
			// else if (word[i] == 'U' || word[i] == 'f' || word[i] == 't')
			// 	ft_add_char_to_string(flags, word[i]);
		}
		i++;
	}
	ft_strdel(&known_flags);
}

void ft_parse_names(char* word, t_lis** names) {
	ft_list_add(names, word);
}

void ft_parse_word(char* word, t_info* info) {
	if (word[0] == '-') {
		ft_parse_flag(word, &(info->flags));
	} else {
		ft_parse_names(word, &(info->names));
	}
}

void ft_parse_input(int argc, char **argv, t_info* info) {
	int i;

	if (argc == 1) {
		ft_list_add(&(info->names), ".");
		return;
	}
	i = 1;
	while (i < argc) {
		ft_parse_word(argv[i], info);
		i++;
	}
	if (!info->names) {
		ft_list_add(&(info->names), ".");
	}
}
