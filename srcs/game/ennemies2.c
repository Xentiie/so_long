/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:56:40 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 17:00:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include "mmath.h"
#include "utils.h"
#include "random.h"
#include <math.h>

void	update_pos_ennemy(void)
{
	if (g_ame->ennemy->is_moving != 1)
		return ;
	g_ame->ennemy->ennemy_pos = v2(
			g_ame->ennemy->ennemy_pos.x + g_ame->ennemy->dir.x,
			g_ame->ennemy->ennemy_pos.y + g_ame->ennemy->dir.y);
	if (distance(
			v2_f(g_ame->player->player_pos.x, g_ame->player->player_pos.y),
			v2_f(g_ame->ennemy->ennemy_pos.x, g_ame->ennemy->ennemy_pos.y))
		< 5 && g_ame->time > 20)
		quit_signal();
	if (distance(v2_f(g_ame->ennemy->ennemy_pos.x, g_ame->ennemy->ennemy_pos.y),
			v2_f(g_ame->ennemy->next_pos.x, g_ame->ennemy->next_pos.y)) < 0.1)
	{
		g_ame->ennemy->ennemy_pos = g_ame->ennemy->next_pos;
		g_ame->ennemy->is_moving = 0;
	}
}

t_color	eval_ennemy(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;

	if (data.local_pos.x > 0.85 || data.local_pos.x < 0.15
		|| data.local_pos.y > 0.85 || data.local_pos.y < 0.15)
		return (new_color(0, 0, 0, 0));
	data.local_pos.x = map(data.local_pos.x, v2_f(0.15, 0.85), v2_f(0, 1));
	data.local_pos.y = map(data.local_pos.y, v2_f(0.15, 0.85), v2_f(0, 1));
	p = v2(
			lerp(0, g_ame->ennemy->current->size->x, data.local_pos.x),
			lerp(0, g_ame->ennemy->current->size->y, data.local_pos.y));
	p.x = clamp(0, g_ame->ennemy->current->size->x, p.x);
	p.y = clamp(0, g_ame->ennemy->current->size->y, p.y);
	out = getpixel(g_ame->ennemy->current, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}
