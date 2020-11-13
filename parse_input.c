#include "ft_ls.h"

void ft_parse_flag(char* word, char** flags) {
	char* known_flags;
	int i;

	i = 1;
	known_flags = ft_strdup("lRart1goUfS");
	while (word[i] != '\0') {
		if (!ft_strchr(known_flags, word[i])) {
			ft_wrong_flag(word[i]);
		}
		else {
			if (!(*flags) || !ft_strchr(*flags, word[i]) || word[i] == 'l' || word[i] == '1' ||
				word[i] == 'o' || word[i] == 'g') {
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
	static int is_end_option;

	if (!ft_strcmp(word, "--") && !is_end_option) {
		is_end_option = 1;
		return ;
	}

	if (!is_end_option && !is_end_option && word[0] == '-' && ft_strcmp(word, "-")) {
		// ft_printf("0 %s %d\n", word, ft_strcmp(word, "-"));
		ft_parse_flag(word, &(info->flags));
	} else {
		// ft_printf("1 %s %d\n", word, ft_strcmp(word, "-"));
		ft_parse_names(word, &(info->names));
		is_end_option = 1;
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
