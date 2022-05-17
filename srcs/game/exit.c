/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

#include <stdlib.h>

#define ANIM_FRAMES 30.0

void update_exit(t_rendering_element *elem)
{
	float	t;
	t_vector2	pos;
	t_vector2	size;

	if (g_ame->time % (int)(ANIM_FRAMES / 5) != 0)
		return ;
	t = frac(g_ame->time / (ANIM_FRAMES) / 2);
	g_ame->portail_curr = eval_anim(g_ame->portail, t);
	pos = *elem->element_pos;
	size = elem->element_size;
	update(pos, size, -1);
}

t_color	eval_exit(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;

    if (g_ame->player->player_pos.x == data.element_pos->x
		&& g_ame->player->player_pos.y == data.element_pos->y)
    {
	    quit_signal();
	}
	p = v2(lerp(0, g_ame->portail_curr->size->x, data.local_pos.x), lerp(0, g_ame->portail_curr->size->y, data.local_pos.y));
	out = getpixel(g_ame->portail_curr, p.x, p.y);
    out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}
