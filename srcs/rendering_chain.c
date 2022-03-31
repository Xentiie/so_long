/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:34:28 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 18:49:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "libft.h"
#include "images.h"
#include <stdlib.h>
#include "logger.h"

static t_list	*g_rendering_chain;

int	is_inside_rectangle(int x, int y, t_vector2 rectangle_pos,
		t_vector2 rectangle_size)
{
	if (x >= rectangle_pos.x && x <= rectangle_pos.x + rectangle_size.x)
	{
		if (y >= rectangle_pos.y && y <= rectangle_pos.y + rectangle_size.y)
			return (1);
	}
	return (0);
}

t_color	get_pixel_at(int x, int y, int *e_lay)
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
		if (is_inside_rectangle(x, y, elem->element_pos,
				elem->element_size))
			if (elem->layer > rem->layer && elem->layer < *e_lay)
				rem = elem;
		curr = curr->next;
	}
	if (!rem)
	{
		ft_log(VERBOSE, "/!\\ Remainder is null");
		return ((t_color){.r = 0, .g = 0, .b = 0, .a = 0});
	}
	data = (t_rendering_data){
		.global_pos = (t_vector2){.x = x, .y = y},
		.local_pos = (t_vector2){.x = x - rem->element_pos.x,
		.y = y - rem->element_pos.y}};
	*e_lay = rem->layer;
	return (rem->eval(data));
}

/*
	Ajoute un element a la chaine de render.
*/
void	add_graphics(t_color (*eval)(t_rendering_data),
			int layer, t_vector2 pos, t_vector2 size)
{
	t_list				*new_elem;
	t_rendering_element	*element;

	element = malloc(sizeof(t_rendering_element));
	element->element_pos = pos;
	element->element_size = size;
	element->layer = layer;
	element->eval = eval;
	new_elem = ft_lstnew(element);
	ft_lstadd_back(&g_rendering_chain, new_elem);
}

void	update(t_image *img, t_vector2 screen_size)
{
	t_vector2	xy;
	int			layer;
	t_color		c;

	xy = (t_vector2){.x = 0, .y = 0};
	while (xy.y < screen_size.y)
	{
		while (xy.x < screen_size.x)
		{
			layer = 1000;
			c = get_pixel_at(xy.x, xy.y, &layer);
			while (c.a == 0)
			{
				if (layer == 0)
					c = (t_color){.a = 1, .r = 0, .g = 0, .b = 0};
				else
					c = get_pixel_at(xy.x, xy.y, &layer);
				layer--;
			}
			putpixel(img, xy.x, xy.y, create_rgb(c.r, c.g, c.b));
			xy.x++;
		}
		xy.x = 0;
		xy.y++;
	}
}
