/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:23:22 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/16 18:36:03 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parse_flag(char *word, char **flags)
{
	char	*known_flags;
	int		i;

	i = 1;
	known_flags = ft_strdup("lRart1goUfS");
	while (word[i] != '\0')
	{
		if (!ft_strchr(known_flags, word[i]))
			ft_wrong_flag(word[i]);
		else if (!(*flags) || !ft_strchr(*flags, word[i]) ||
						word[i] == 'l' || word[i] == '1' ||
						word[i] == 'o' || word[i] == 'g')
		{
			ft_add_char_to_string(flags, word[i]);
		}
		i++;
	}
	ft_strdel(&known_flags);
}

void	ft_parse_word(char *word, t_info *info)
{
	static int is_end_option;

	if (!ft_strcmp(word, "--") && !is_end_option)
	{
		is_end_option = 1;
		return ;
	}
	if (!is_end_option && word[0] == '-' && ft_strcmp(word, "-"))
		ft_parse_flag(word, &(info->flags));
	else
	{
		ft_list_add_begin(&(info->names), word);
		is_end_option = 1;
	}
}

void	ft_parse_input(int argc, char **argv, t_info *info)
{
	int i;

	if (argc == 1)
	{
		ft_list_add(&(info->names), ".");
		return ;
	}
	i = 1;
	while (i < argc)
	{
		ft_parse_word(argv[i], info);
		i++;
	}
	if (!info->names)
		ft_list_add(&(info->names), ".");
}
