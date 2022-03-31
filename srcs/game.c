/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:26:00 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 11:22:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*read_all_file(int fd, int read_size)
{
	char	*buffer;
	char	*out;
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	out = malloc(sizeof(char));
	out[0] = '\0';
	while (bytes_read > 0)
	{
		buffer = malloc(read_size * sizeof(char));
		bytes_read = read(fd, buffer, read_size);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		tmp = out;
		out = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (out);
}
