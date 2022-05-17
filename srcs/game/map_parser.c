/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:47:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:45:52 by reclaire         ###   ########.fr       */
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

void	is_all_one(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			error_signal("Invalid map ! Les murs ne sont pas que des '1'.");
		i++;
	}
}

char	*get_map(int fd)
{
	char		*out;
	char		**splitted;
	int			i;
	size_t		len;

	out = read_all_file(fd, 10);
	if (!ft_strchr(out, 'E') || !ft_strchr(out, 'C') || !ft_strchr(out, 'P'))
		error_signal("Invalid map ! Toute les charactères ne sont pas présents.");
	i = 0;
	len = -1;
	splitted = ft_split(out, '\n');
	if (!splitted)
		error_signal("Invalid map !");
	is_all_one(splitted[0]);
	while (splitted[i])
	{
		if ((int)len != -1 && ft_strlen(splitted[i]) != len)
			error_signal("Invalid map ! Les lignes ne font pas la même longueur.");
		len = ft_strlen(splitted[i]);
		if (!splitted[i + 1] || i == 0)
			is_all_one(splitted[i]);
		else
		{
			if (splitted[i][0] != '1' || splitted[i][len - 1] != '1')
				error_signal("Invalid map ! Les murs ne sont pas que des '1'.");
		}
		free(splitted[i]);
		i++;
	}
	free(splitted);
	if (i == 0)
		error_signal("Invalid map !");
	return (out);
}

t_tile_type	**parse_map(char *file_path, int *size_x, int *size_y)
{
	int				fd;
	char			*str;
	t_tile_type		**out;
	t_vector2		current;

	is_filename_valid(file_path);
	fd = open(file_path, O_RDONLY);
	str = get_map(fd);
	*size_x = (ft_strchr(str, '\n') - str);
	*size_y = count_chars(str, '\n') + 1;
	current = (t_vector2){.x = 0, .y = 0};
	out = mmalloc(*size_y * sizeof(t_tile_type *));
	while (current.y < *size_y)
	{
		out[current.y] = mmalloc((*size_x) * sizeof(t_tile_type));
		while (current.x < *size_x)
		{
			out[current.y][current.x] = parse_c(str[current.x
					+ current.y * (*size_x) + current.y]);
			if (out[current.y][current.x] == ITEM)
				g_ame->item_count++;
			if (out[current.y][current.x] == EXIT)
				g_ame->exit_pos = pv2(current.x * PIXEL_PER_TILE, current.y * PIXEL_PER_TILE - 30);
			current.x++;
		}
		current.x = 0;
		current.y++;
	}
	free(str);
	return (out);
}
