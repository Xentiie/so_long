/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:01:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

#include <stdlib.h>

#define ANIM_FRAMES 30.0

void	update_exit(t_rendering_element *elem)
{
	float	t;

	if (g_ame->time % (int)(ANIM_FRAMES / 5) != 0)
		return ;
	t = frac(g_ame->time / (ANIM_FRAMES) / 2);
	g_ame->portail_curr = eval_anim(g_ame->portail, t);
	if (distance(
			v2_f(g_ame->player->player_pos.x, g_ame->player->player_pos.y),
			v2_f(elem->element_pos->x, elem->element_pos->y)) < 5)
		quit_signal();
}

t_color	eval_exit(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;

	p = v2(lerp(0, g_ame->portail_curr->size->x, data.local_pos.x),
			lerp(0, g_ame->portail_curr->size->y, data.local_pos.y));
	out = getpixel(g_ame->portail_curr, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}
