/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:34:28 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include "libft.h"
#include "mmath.h"
#include "images.h"
#include <stdlib.h>

#include <math.h>

#define PIXEL_AMOUNT 235

int	is_inside_rectangle(int x, int y, t_vector2 *rectangle_pos,
		t_vector2 rectangle_size)
{
	if (x >= rectangle_pos->x && x <= rectangle_pos->x + rectangle_size.x)
	{
		if (y >= rectangle_pos->y && y <= rectangle_pos->y + rectangle_size.y)
		{
			return (1);
		}
	}
	return (0);
}

void	putblock(t_vector2 pos, t_color c)
{
	putpixel(g_ame->render_img, pos.x, pos.y, c);
	putpixel(g_ame->render_img, pos.x + 1, pos.y, c);
	putpixel(g_ame->render_img, pos.x + 2, pos.y, c);
	putpixel(g_ame->render_img, pos.x, pos.y + 1, c);
	putpixel(g_ame->render_img, pos.x + 1, pos.y + 1, c);
	putpixel(g_ame->render_img, pos.x + 2, pos.y + 1, c);
	putpixel(g_ame->render_img, pos.x, pos.y + 2, c);
	putpixel(g_ame->render_img, pos.x + 1, pos.y + 2, c);
	putpixel(g_ame->render_img, pos.x + 2, pos.y + 2, c);
}

t_color	get_pixel_at(int x, int y, int *e_lay, int except_lay)
{
	t_rendering_element	*rem;
	t_rendering_element	*elem;
	t_rendering_data	data;
	t_list				*curr;

	curr = g_rendering_chain;
	rem = (t_rendering_element *)curr->content;
	while (curr)
	{
		elem = (t_rendering_element *)curr->content;
		if (except_lay != -1 && elem->layer == except_lay)
		{
			curr = curr->next;
			continue ;
		}
		if (is_inside_rectangle(x, y, elem->element_pos,
				elem->element_size))
		{
			if (elem != rem && rem->layer > *e_lay)
				rem = elem;
			if (elem->layer > rem->layer && elem->layer <= *e_lay)
				rem = elem;
		}
		curr = curr->next;
	}
	data = (t_rendering_data){
		.global_pos = v2(
			x,
			y
		),
		.local_pos = v2_f(
			inverse_lerp(rem->element_pos->x, rem->element_pos->x + rem->element_size.x, x),
			inverse_lerp(rem->element_pos->y, rem->element_pos->y + rem->element_size.y, y)),
		.element_pos = rem->element_pos,
		.element_size = rem->element_size,
		.self = rem};
	*e_lay = rem->layer;
	return (rem->eval(data));
}

void	update(t_vector2 xy, t_vector2 size, int except_lay)
{
	int			layer;
	int			layer2;
	t_color		c;
	t_vector2	uv_pixelised;
	t_vector2	pos;

	pos = v2(xy.x, xy.y);
	size = v2(pos.x + size.x, pos.y + size.y);
	while (pos.y < size.y)
	{
		while (pos.x < size.x)
		{
			layer = 1000;
			//uv_pixelised = pixelize(pos, *(g_ame->screen_dim));
			uv_pixelised = pos;
			c = get_pixel_at(uv_pixelised.x, uv_pixelised.y, &layer, except_lay);
			while (c.a == 0)
			{
				layer--;
				layer2 = layer;
				if (layer < 0)
					c = (t_color){.a = 1, .r = 0, .g = 0, .b = 0};
				else
					c = get_pixel_at(uv_pixelised.x, uv_pixelised.y, &layer2, except_lay);
			}
			putblock(pos, c);
			pos.x += 3;
		}
		pos.x = xy.x;
		pos.y += 3;
	}
}
