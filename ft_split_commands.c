/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:16:55 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/03/01 14:01:28 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"

static int	ft_word_count(char *s)
{
	int	words;
	int	i;

	words = 1;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == 32 && s[i + 1] == '-')
			words++;
		if (s[i] == 32 && s[i + 1] != '-' && s[i + 1] != 0)
		{
			words++;
			return (words);
		}
		i++;
	}
	return (words);
}

static int	ft_len_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != 32)
		i++;
	return (i);
}

static char	*ft_remove_quotes(char *s)
{
	char	*trim_str;

	if (s != NULL)
	{
		trim_str = ft_strtrim(s, "'");
		if (trim_str == NULL)
			return (NULL);
		if (ft_strncmp(s, trim_str, ft_strlen(s)) == 0)
		{
			free(trim_str);
			trim_str = ft_strtrim(s, "\"");
			if (trim_str == NULL)
				return (NULL);
		}
		return (trim_str);
	}
	return (NULL);
}

static char	*ft_return_str(char *s, int first_word)
{
	int		i;
	int		j;
	char	*str;
	char	*trim_str;

	i = 0;
	if (ft_find_flag(s) == 1 || first_word == 1)
	{
		while (s[i] != 0 && s[i] != 32)
			i++;
		str = (char *)malloc((i + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		j = 0;
		while (s[j] != 0 && s[j] != 32)
		{
			str[j] = s[j];
			j++;
		}
		str[j] = 0;
		trim_str = ft_remove_quotes(str);
		free(str);
		return (trim_str);
	}
	return (ft_remove_quotes(s));
}

char	**ft_return_commands(char *s)
{
	char	**commands;
	int		pos;
	int		len;
	int		first_word;

	commands = (char **)malloc((ft_word_count(s) + 1) * sizeof(char *));
	if (commands == NULL)
		return (NULL);
	commands[ft_word_count(s)] = NULL;
	pos = 0;
	len = 0;
	first_word = 1;
	while (pos < ft_word_count(s))
	{
		commands[pos] = ft_return_str(&s[len], first_word);
		if (commands[pos] == NULL)
		{
			ft_free_char_pp(commands);
			return (NULL);
		}
		len = len + ft_len_word(&s[len]) + 1;
		pos++;
		first_word++;
	}
	return (commands);
}
