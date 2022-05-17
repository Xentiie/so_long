/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:18:53 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random.h"
#include "mmath.h"
#include <math.h>


#define SCALE 2.5
#define BASE_ROUGHNESS 1
#define ROUGHNESS 2
#define PERSISTENCE 0.5
#define NUM_LAYERS 3

float	lpnoise(float x, float y, t_vector2_f offset)
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
	y = lerp(1, 0, y);
	while (i < NUM_LAYERS)
	{
		v = pnoise(
				x * frequency * SCALE + offset.x,
				y * frequency * SCALE * lerp(1, 2.7, y) + offset.y);
		noise_value += (v + 1) * .5f * amplitude;
		frequency *= ROUGHNESS;
		amplitude *= PERSISTENCE;
		i++;
	}
	return (noise_value);
}

float	lpnoise_custom(float x, float y, t_noise_data data)
{
	float	noise_value;
	float	frequency;
	float	amplitude;
	float	v;
	int		i;

	noise_value = 0;
	frequency = data.base_roughness;
	amplitude = 1;
	i = 0;
	while (i < data.layers)
	{
		v = pnoise(
				x * frequency * data.scale.x,
				y * frequency * data.scale.y);
		noise_value += (v + 1) * .5f * amplitude;
		frequency *= data.rougness;
		amplitude *= data.persistence;
		i++;
	}
	return (noise_value);
}

float	rnd(int *seed)
{
	(*seed)++;
	return (frac(sin((double)*seed * 43758.5453123)));
}

float	rnd_range(float min, float max, int *seed)
{
	return (fabs(rnd(seed)) * (max - min) + min);
}

float	grad2( int hash, float x, float y)
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
