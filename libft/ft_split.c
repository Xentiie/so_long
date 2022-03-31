/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 08:09:13 by swalter           #+#    #+#             */
/*   Updated: 2022/03/03 15:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	char_is_separator(char c, char charset)
{
	int	i;

	i = 0;
	if (c == charset || c == '\0')
		return (1);
	return (0);
}

static	int	count_words(char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], charset) == 1
			&& char_is_separator(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

static	void	write_word(char *dest, char *from, char charset)
{
	int	i;

	i = 0;
	while (char_is_separator(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static	int	write_split(char **split, char *str, char charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (char_is_separator(str[i + j], charset) == 0)
				j++;
			split[word] = malloc(sizeof(char) * (j + 1));
			if (split[word] == NULL)
				return (0);
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	words = count_words((char *)s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	res[words] = 0;
	if (!write_split(res, (char *)s, c))
		return (NULL);
	return (res);
}