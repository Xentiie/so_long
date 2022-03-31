/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:40:37 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 22:09:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "noise.h"
#include "images.h"
#include "game.h"
#include "mmath.h"
#include <stdio.h>

#define SEA_LEVEL 0.4
#define SAND_WIDTH 0.2

t_color	eval_sea_color(float v)
{
	t_color	ocean_light;
	t_color	ocean_dark;

	v = map(v, (t_vector2_f){.x = 0, .y = SEA_LEVEL},
			(t_vector2_f){.x = 0, .y = 1});
	ocean_light = (t_color){.a = 1, .r = 55, .g = 170, .b = 237};
	ocean_dark = (t_color){.a = 1, .r = 55, .g = 85, .b = 237};
	return (lerp_color(ocean_dark, ocean_light, v));
}

t_color	eval_ground_color(float v)
{
	t_color	sand;
	t_color	ground_light;
	t_color	ground_dark;

	sand = (t_color){.a = 1, .r = 237, .g = 195, .b = 55};
	ground_light = (t_color){.a = 1, .r = 50, .g = 184, .b = 65};
	ground_dark = (t_color){.a = 1, .r = 35, .g = 130, .b = 46};
	v = map(v, (t_vector2_f){.x = SEA_LEVEL, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SAND_WIDTH)
	{
		v = map(v, (t_vector2_f){.x = 0, .y = SAND_WIDTH},
				(t_vector2_f){.x = 0, .y = 1});
		return (lerp_color(sand, ground_light, v));
	}
	else
	{
		return (lerp_color(ground_light, ground_dark, v));
	}
}

t_color	eval_bg(t_rendering_data data)
{
	float	v;

	v = get_point(data.global_pos.x, data.global_pos.y);
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1.3},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
	{
		v = get_point(data.global_pos.x + sin(0.5), data.global_pos.y + sin(0.5));
		return (eval_sea_color(v));
	}
	else
		return (eval_ground_color(v));
	//return ((t_color){.a = 1, .r = v * 255, .g = v * 255, .b = v * 255});
}
