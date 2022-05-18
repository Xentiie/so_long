/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:40:37 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 16:52:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "random.h"
#include "images.h"
#include "game.h"
#include "mmath.h"
#include <math.h>

t_color	eval_sea_color(float v)
{
	t_color	ocean_light;
	t_color	ocean_dark;
	t_color	out;

	v = map(v, (t_vector2_f){.x = 0, .y = SEA_LEVEL},
			(t_vector2_f){.x = 0, .y = 1});
	ocean_light = (t_color){.a = 1, .r = 66, .g = 194, .b = 245};
	ocean_dark = (t_color){.a = 1, .r = 22, .g = 46, .b = 102};
	out = lerp_color(ocean_dark, ocean_light, clampf(0, 1, v));
	return (out);
}

t_color	eval_ground_color(float v)
{
	t_color	sand;
	t_color	ground_light;
	t_color	ground_dark;

	sand = (t_color){.a = 1, .r = 237, .g = 195, .b = 55};
	ground_light = (t_color){.a = 1, .r = 50, .g = 184, .b = 65};
	ground_dark = (t_color){.a = 1, .r = 35, .g = 150, .b = 46};
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
		v = map(v, (t_vector2_f){.x = SAND_WIDTH, .y = 1},
				(t_vector2_f){.x = 0, .y = 1});
		return (lerp_color(ground_light, ground_dark, v));
	}
}

t_color	eval_background(t_rendering_data data)
{
	float		v;
	t_vector2_f	global_uv;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = lpnoise(global_uv.x, global_uv.y, v2_f(g_ame->seed, g_ame->seed));
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
		return (eval_sea_color(v));
	else
		return (eval_ground_color(v));
}

t_color	eval_background2(t_rendering_data data)
{
	float		v;
	t_vector2_f	global_uv;

	return (new_color(data.local_pos.x * 255, data.local_pos.y * 255, 0, 1));
	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = lpnoise(global_uv.x, global_uv.y, v2_f(g_ame->seed, g_ame->seed));
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
		return (eval_sea_color(v));
	else
		return (eval_ground_color(v));
}
