/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:40:19 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/05 21:40:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mmath.h"

t_color	eval_count1(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;
	t_image		*img;

	img = g_ame->nums->sprites[g_ame->mov_counter % 10];
	p = v2(lerp(0, img->size->x, data.local_pos.x),
			lerp(0, img->size->y, data.local_pos.y));
	p.x = minimum(p.x, 63);
	p.y = minimum(p.y, 63);
	out = getpixel(img, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}

t_color	eval_count2(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;
	t_image		*img;

	img = g_ame->nums->sprites[g_ame->mov_counter / 10];
	p = v2(lerp(0, img->size->x, data.local_pos.x),
			lerp(0, img->size->y, data.local_pos.y));
	p.x = minimum(p.x, 63);
	p.y = minimum(p.y, 63);
	out = getpixel(img, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}

void	init_counter(void)
{
	add_graphics(&eval_count2, 3, pv2(0, 0),
		v2(g_ame->pixel_per_tile, g_ame->pixel_per_tile));
	add_graphics(&eval_count1, 4, pv2(g_ame->pixel_per_tile + 1, 0),
		v2(g_ame->pixel_per_tile, g_ame->pixel_per_tile));
}
