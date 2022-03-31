/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:00:43 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:50:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"
#include "mmath.h"
#include "ttypes.h"
#include "libft.h"
#include "game.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

float	grad2( int hash, float x, float y )
{
	int		h;
	float	u;
	float	v;

	h = hash & 7;
	if (h < 4)
	{
		u = x;
		v = y;
	}
	else
	{
		u = y;
		v = x;
	}
	if ((h & 1))
		u *= -1;
	if ((h & 2))
		v = -2.0 * v;
	else
		v = 2.0 * v;
	return (u + v);
}

float	noise2(float x, float y, int *perm)
{
	t_vector4	i1i2;
	t_vector4_f	f0f1;
	t_vector4_f	nx_n;
	float		s;
	float		t;

	i1i2.x = floor(x);
	i1i2.y = floor(y);
	f0f1.x = x - i1i2.x;
	f0f1.y = y - i1i2.y;
	f0f1.z = f0f1.x - 1.0f;
	f0f1.w = f0f1.y - 1.0f;
	i1i2.z = (i1i2.x + 1) & 0xff;
	i1i2.w = (i1i2.y + 1) & 0xff;
	i1i2.x = i1i2.x & 0xff;
	i1i2.y = i1i2.y & 0xff;
	t = fade(f0f1.y);
	s = fade(f0f1.x);
	nx_n.x = grad2(perm[i1i2.x + perm[i1i2.y]], f0f1.x, f0f1.y);
	nx_n.y = grad2(perm[i1i2.x + perm[i1i2.w]], f0f1.x, f0f1.w);
	nx_n.z = lerp(nx_n.x, nx_n.y, t);
	nx_n.x = grad2(perm[i1i2.z + perm[i1i2.y]], f0f1.z, f0f1.y);
	nx_n.y = grad2(perm[i1i2.z + perm[i1i2.w]], f0f1.z, f0f1.w);
	nx_n.w = lerp(nx_n.x, nx_n.y, t);
	return (0.507f * (lerp(nx_n.z, nx_n.w, s)));
}

static int	*parse_permutations(char *str)
{
	int		i;
	int		j;
	int		*permutation;

	i = 0;
	j = 0;
	permutation = malloc(sizeof(int) * 256);
	while (str[i] != '\0')
	{
		permutation[j] = ft_atoi(str + i);
		i += ft_magnitude(permutation[j]);
		i++;
		j++;
	}	
	return (permutation);
}

int	*load_permutation(char *fileName)
{
	int		fd;
	int		i;
	int		*permutation;
	int		*p;
	char	*str;

	fd = open(fileName, O_RDONLY);
	i = 0;
	str = read_all_file(fd, 25);
	close(fd);
	permutation = parse_permutations(str);
	free(str);
	i = 0;
	p = malloc(sizeof(int) * 512);
	while (i < 256)
	{
		p[i] = permutation[i];
		p[256 + i] = permutation[i];
		i++;
	}
	free(permutation);
	return (p);
}
