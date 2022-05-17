/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnoise.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:00:43 by reclaire          #+#    #+#             */
/*   Updated: 2022/04/07 17:37:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random.h"
#include "ttypes.h"
#include "mmath.h"
#include "utils.h"
#include "game.h"
#include "libft.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

static int *g_perm;

static int	*parse_permutations(char *str)
{
	int		i;
	int		j;
	int		*permutation;

	i = 0;
	j = 0;
	permutation = mmalloc(sizeof(int) * 256);
	while (str[i] != '\0')
	{
		permutation[j] = ft_atoi(str + i);
		i += ft_magnitude(permutation[j]);
		i++;
		j++;
	}	
	return (permutation);
}

static int	*load_permutation(char *fileName)
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
	p = mmalloc(sizeof(int) * 512);
	while (i < 256)
	{
		p[i] = permutation[i];
		p[256 + i] = permutation[i];
		i++;
	}
	free(permutation);
	return (p);
}

void	free_perms(void)
{
	free(g_perm);
}

void	init_noise(void)
{
	if (!g_perm)
		g_perm = load_permutation("files/perms.txt");
}

float	pnoise(float x, float y)
{
	t_vector4	i1i2;
	t_vector4_f	f0f1;
	t_vector4_f	nx_n;
	t_vector2_f	t_s;

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
	t_s.x = fade(f0f1.y);
	t_s.y = fade(f0f1.x);
	nx_n.x = grad2(g_perm[i1i2.x + g_perm[i1i2.y]], f0f1.x, f0f1.y);
	nx_n.y = grad2(g_perm[i1i2.x + g_perm[i1i2.w]], f0f1.x, f0f1.w);
	nx_n.z = lerp(nx_n.x, nx_n.y, t_s.x);
	nx_n.x = grad2(g_perm[i1i2.z + g_perm[i1i2.y]], f0f1.z, f0f1.y);
	nx_n.y = grad2(g_perm[i1i2.z + g_perm[i1i2.w]], f0f1.z, f0f1.w);
	return (0.507f * (lerp(nx_n.z, lerp(nx_n.x, nx_n.y, t_s.x), t_s.y)));
}
