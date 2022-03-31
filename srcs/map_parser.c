/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:47:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 18:23:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <fcntl.h>
#include <logger.h>
#include <unistd.h>

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

char	*get_map(int fd)
{
	char		*out;
	char		**splitted;
	int			i;
	size_t		len;

	out = read_all_file(fd, 10);

	//ENCADRE PAR DES MURS
	//Si erreur:	quitter et ecrire Erreur\nMessage
	
	if (!ft_strchr(out, 'E') || !ft_strchr(out, 'C') || !ft_strchr(out, 'P'))
		register_error("Invalid map !");
	i = 0;
	len = -1;
	splitted = ft_split(out, '\n');
	if (!splitted)
		register_error("Invalid map !");
	while (splitted[i])
	{
		if ((int)len != -1 && ft_strlen(splitted[i]) != len)
			register_error("Invalid map !");
		len = ft_strlen(splitted[i]);
		i++;
	}
	if (i == 0)
		register_error("Invalid map !");
	return (out);
}

t_tile_type	**parse_map(char *file_path, int *size_x, int *size_y)
{
	int				fd;
	char			*str;
	t_tile_type		**out;
	t_vector2		current;

	fd = open(file_path, O_RDONLY);
	str = get_map(fd);
	*size_x = ft_strchr(str, '\n') - str;
	*size_y = count_chars(str, '\n') + 1;
	current = (t_vector2){.x = 0, .y = 0};
	out = malloc(*size_y * sizeof(t_tile_type *));
	while (current.y < *size_y)
	{
		out[current.y] = malloc((*size_x) * sizeof(t_tile_type));
		while (current.x < *size_x)
		{
			out[current.y][current.x] = parse_c(str[current.x
					+ current.y * (*size_x) + current.y]);
			current.x++;
		}
		current.x = 0;
		current.y++;
	}
	free(str);
	return (out);
}
