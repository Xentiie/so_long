/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:58:50 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 14:58:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

t_color	eval_sky2(t_rendering_data data)
{
	t_vector2_f	global_uv;
	float		v;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = fabs(lpnoise(global_uv.x * 2,
				global_uv.y, v2_f(g_ame->seed, g_ame->seed)));
	if (v > 0.91)
		return (new_color(255 / v / 1.1, 255 / v / 1.1, 255 / v / 1.1, 1));
	return (new_color(30, 160, 250, 1));
}

t_color	eval_sky(t_rendering_data data)
{
	t_vector2_f	global_uv;
	t_color		out;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	if (is_inside(global_uv))
			out = eval_background(data);
	else
	{
		if (global_uv.y <= 0.5)
			out = new_color(0, 0, 0, 0);
		else
			out = eval_ground(global_uv);
	}
	return (out);
}
