/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:18:41 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 15:18:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

void	is_filename_valid(char *str)
{
	int	i;

	i = ft_strlen(str);
	i -= 4;
	if (ft_strcmp(str + i, ".ber") != 0)
		error_signal("Invalid map ! File not ending in '.ber'.");
}

t_tile_type	parse_c(char c)
{
	t_tile_type	out;

	if (c == '0')
		out = EMPTY;
	if (c == '1')
		out = WALL;
	if (c == 'C')
		out = ITEM;
	if (c == 'E')
		out = EXIT;
	if (c == 'P')
		out = SPAWN;
	return (out);
}

int	count_chars(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
