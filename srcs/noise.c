/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:18:53 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 21:31:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"
#include "mmath.h"
#include "game.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

#define SCALE 5
#define BASE_ROUGHNESS 1.2
#define ROUGHNESS 1.8
#define PERSISTENCE 0.5
#define NUM_LAYERS 3

int	*g_p;

float	layered_noise(int x, int y, int *g_p)
{
	float	noise_value;
	float	frequency;
	float	amplitude;
	float	v;
	int		i;

	noise_value = 0;
	frequency = BASE_ROUGHNESS;
	amplitude = 1;
	i = 0;
	while (i < NUM_LAYERS)
	{
		v = noise2(
				x * frequency / g_ame->screen_size->x * SCALE,
				y * frequency / g_ame->screen_size->y
				/ (g_ame->screen_size->x / g_ame->screen_size->y) * SCALE,
				g_p);
		noise_value += (v + 1) * .5f * amplitude;
		frequency *= ROUGHNESS;
		amplitude *= PERSISTENCE;
		i++;
	}
	return (noise_value);
}

float	get_point(int x, int y)
{
	float	v;

	if (!g_p)
		g_p = load_permutation("perms.txt");
	v = layered_noise(x, y, g_p);
	return (v);
}
