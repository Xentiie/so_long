/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:40:37 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 14:59:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

#define ELLIPSE_SIZE_X 0.55
#define ELLIPSE_SIZE_Y 0.45
#define ELLIPSE_POS_X 0.5
#define ELLIPSE_POS_Y 0.43
#define UPDATE_RATE 1

int	is_inside(t_vector2_f p)
{
	return (
		powf(p.x - ELLIPSE_POS_X, 2) / powf(ELLIPSE_SIZE_X, 2)
		+ powf(p.y - ELLIPSE_POS_Y, 2) / powf(ELLIPSE_SIZE_Y, 2) <= 1
	);
}

void	update_waterfall(t_rendering_element *elem)
{
	t_vector2	pos;
	t_vector2	size;

	pos = *elem->element_pos;
	size = elem->element_size;
	update(pos, size, -1);
}

t_color	eval_waterfall(t_rendering_data data)
{
	float		v;
	t_vector2_f	global_uv;
	t_color		ocean_light;
	t_color		ocean_dark;
	t_color		out;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = pnoise(global_uv.x * 100, global_uv.y * 15 - g_ame->time / 6.5);
	ocean_light = (t_color){.a = 1, .r = 66, .g = 194, .b = 245};
	ocean_dark = (t_color){.a = 1, .r = 22, .g = 46, .b = 102};
	out = lerp_color(ocean_light, ocean_dark, v);
	return (out);
}

t_color	eval_ground2(t_vector2_f uv, t_vector2_f p_above)
{
	float				v;
	float				y;
	t_color				out;
	t_rendering_data	data2;

	if (distance(uv, p_above) < 0.02)
		return (new_color(35, 150, 46, 1));
	data2.global_pos = v2(
			(int)(p_above.x * g_ame->screen_dim->x),
			(int)(p_above.y * g_ame->screen_dim->y));
	y = powf(uv.x, 2) + 0.25;
	v = pnoise(y * uv.x * 10, y * uv.y * 40);
	out = lerp_color(new_color(100, 70, 27, 1), new_color(190, 130, 50, 1), v);
	out = lerp_color(out, eval_background(data2),
			inverse_lerp(0.05, 0, distance(uv, p_above)));
	return (out);
}

t_color	eval_ground(t_vector2_f uv)
{
	t_vector2_f			p_above;
	float				v;

	p_above = uv;
	while (!is_inside(p_above))
		p_above.y -= 1.0 / (g_ame->screen_dim->y);
	v = lpnoise(p_above.x, p_above.y, v2_f(g_ame->seed, g_ame->seed));
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
		return (new_color(0, 0, 0, 0));
	return (eval_ground2(uv, p_above));
}
