/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:47:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 15:23:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

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

char	*get_map2(int fd, int *i, size_t *len, char ***splitted)
{
	char	*out;

	out = read_all_file(fd, 10);
	if (!ft_strchr(out, 'E') || !ft_strchr(out, 'C') || !ft_strchr(out, 'P'))
		error_signal(
			"Invalid map ! Tout les charactères ne sont pas présents.");
	*i = 0;
	*len = -1;
	*splitted = ft_split(out, '\n');
	if (!(*splitted))
		error_signal("Invalid map !");
	is_all_one((*splitted)[0]);
	return (out);
}

char	*get_map(int fd)
{
	char		*out;
	char		**splitted;
	int			i;
	size_t		len;

	out = get_map2(fd, &i, &len, &splitted);
	while (splitted[i])
	{
		if ((int)len != -1 && ft_strlen(splitted[i]) != len)
			error_signal(
				"Invalid map ! Les lignes ne font pas la même longueur.");
		len = ft_strlen(splitted[i]);
		if (!splitted[i + 1] || i == 0)
			is_all_one(splitted[i]);
		else
			if (splitted[i][0] != '1' || splitted[i][len - 1] != '1')
				error_signal("Invalid map ! Les murs ne sont pas que des '1'.");
		free(splitted[i]);
		i++;
	}
	free(splitted);
	if (i == 0)
		error_signal("Invalid map !");
	return (out);
}

char	*parse_map2(char *file_path, int *size_x, int *size_y)
{
	int				fd;
	char			*str;

	is_filename_valid(file_path);
	fd = open(file_path, O_RDONLY);
	str = get_map(fd);
	*size_x = (ft_strchr(str, '\n') - str);
	*size_y = count_chars(str, '\n') + 1;
	return (str);
}

t_tile_type	**parse_map(char *file_path, int *size_x, int *size_y)
{
	char			*str;
	t_tile_type		**out;
	t_vector2		xy;

	str = parse_map2(file_path, size_x, size_y);
	xy = (t_vector2){.x = 0, .y = 0};
	out = mmalloc(*size_y * sizeof(t_tile_type *));
	while (xy.y < *size_y)
	{
		out[xy.y] = mmalloc((*size_x) * sizeof(t_tile_type));
		while (xy.x < *size_x)
		{
			out[xy.y][xy.x] = parse_c(str[xy.x + xy.y * (*size_x) + xy.y]);
			if (out[xy.y][xy.x] == ITEM)
				g_ame->item_count++;
			if (out[xy.y][xy.x] == EXIT)
				g_ame->exit_pos = pv2(xy.x
						* PIXEL_PER_TILE, xy.y * PIXEL_PER_TILE - 30);
			xy.x++;
		}
		xy.x = 0;
		xy.y++;
	}
	free(str);
	return (out);
}
