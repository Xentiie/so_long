/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:42:56 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 16:49:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include "game.h"
#include "rendering.h"
#include "random.h"
#include "mmath.h"
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

void	add_rocks2(t_vector2 pos, int i)
{
	t_vector2	*elem_pos;
	t_vector2_f	rock_p;

	rock_p = v2_f(-5 + (int)rnd_range(-4, 7, &i),
			-5 + (int)rnd_range(-10, 10, &i));
	elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
			pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
	add_graphics(&eval_rocks, 12, elem_pos,
		v2(32, 64));
	rock_p = v2_f(35 + (int)rnd_range(-7, 7, &i),
			5 + (int)rnd_range(-10, 10, &i));
	elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
			pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
	add_graphics(&eval_rocks, 12, elem_pos,
		v2(32, 64));
}

void	add_rocks(t_vector2 pos)
{
	t_vector2	*elem_pos;
	t_vector2_f	rock_p;
	int			i;

	i = g_ame->seed;
	if (rnd(&i) > 0.2f)
		add_rocks2(pos, i);
	else
	{
		rock_p = v2_f((int)rnd_range(5, 20, &i),
				-5 + (int)rnd_range(-10, 10, &i));
		elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
				pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
		add_graphics(&eval_rocks, 12, elem_pos,
			v2(32, 64));
	}
}

/*
	if (keycode == 65307)
		quit_signal();
	if (keycode == 122)
		register_movement(v2(0, -1));
	if (keycode == 113)
		register_movement(v2(-1, 0));
	if (keycode == 115)
		register_movement(v2(0, 1));
	if (keycode == 100)
		register_movement(v2(1, 0));
*/
int	handle_keypress(int keycode, void *useless)
{
	useless = (void *)useless;
	if (keycode == 65307)
		quit_signal();
	if (keycode == 13)
		register_movement(v2(0, -1));
	if (keycode == 0)
		register_movement(v2(-1, 0));
	if (keycode == 1)
		register_movement(v2(0, 1));
	if (keycode == 2)
		register_movement(v2(1, 0));
	return (0);
}

t_color	eval_sky3(t_rendering_data data)
{
	t_vector2_f	global_uv;
	float		v;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = fabs(lpnoise(global_uv.x * 2 + g_ame->time / 200.0,
				global_uv.y, v2_f(g_ame->seed, g_ame->seed)));
	if (v > 0.91)
	{
		return (new_color(255 / v / 1.1, 255 / v / 1.1, 255 / v / 1.1, 1));
	}
	return (new_color(30, 160, 250, 1));
}

t_color	eval_bg(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;
	t_image		*img;

	img = g_ame->background;
	p = v2(lerp(0, img->size->x, data.local_pos.x),
			lerp(0, img->size->y, data.local_pos.y));
	out = getpixel(img, p.x, p.y);
	return (out);
}
