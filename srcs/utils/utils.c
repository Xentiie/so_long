/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:26:00 by reclaire          #+#    #+#             */
/*   Updated: 2022/04/19 16:30:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mmath.h"
#include "game.h"
#include "libft.h"
#include <stdlib.h>

char	*read_all_file(int fd, int read_size)
{
	char	*buffer;
	char	*out;
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	out = mmalloc(sizeof(char));
	out[0] = '\0';
	while (bytes_read > 0)
	{
		buffer = mmalloc((read_size + 1) * sizeof(char));
		bytes_read = read(fd, buffer, read_size);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = out;
		out = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (out);
}

t_vector2	map_to_screen(t_vector2 pos)
{
	t_vector2	out;

	out = v2(
			(pos.x + 1) * g_ame->pixel_per_tile,
			pos.y * g_ame->pixel_per_tile - 30
			);
	return (out);
}

t_vector2	screen_to_map(t_vector2 pos)
{
	t_vector2	out;

	out = v2(
			pos.x / g_ame->pixel_per_tile - 1,
			(pos.y + 30) / g_ame->pixel_per_tile
			);
	return (out);
}

void	*mmalloc(size_t size)
{
	void	*out;

	out = malloc(size);
	if (!out)
		error_signal("Memory error !");
	return (out);
}
