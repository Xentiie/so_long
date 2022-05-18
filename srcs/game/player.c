/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:49:15 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 15:11:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include "mmath.h"
#include "utils.h"
#include "random.h"
#include <math.h>

#include <stdlib.h>

#define UPDATE_RATE 1
#define PLAYER_MOVE_FRAMES 30.0

void	update_sprite_pla2(float t)
{
	if (g_ame->player->player_pos.x - g_ame->player->next_pos.x < 0)
		g_ame->player->current = eval_anim(g_ame->player->anim_lside, t);
	if (g_ame->player->player_pos.x - g_ame->player->next_pos.x > 0)
		g_ame->player->current = eval_anim(g_ame->player->anim_rside, t);
	if (g_ame->player->player_pos.y - g_ame->player->next_pos.y < 0)
		g_ame->player->current = eval_anim(g_ame->player->anim_front, t);
	if (g_ame->player->player_pos.y - g_ame->player->next_pos.y > 0)
		g_ame->player->current = eval_anim(g_ame->player->anim_back, t);
}

void	update_sprite_pla(void)
{
	int		curr_time;
	float	t;

	curr_time = g_ame->time - g_ame->player->start_time;
	if (g_ame->player->is_moving != 1)
		return ;
	t = curr_time / PLAYER_MOVE_FRAMES;
	if (g_ame->player->is_in_water)
	{
		if (g_ame->player->player_pos.x - g_ame->player->next_pos.x > 0)
			g_ame->player->current = eval_anim(g_ame->ship_left, t);
		if (g_ame->player->player_pos.x - g_ame->player->next_pos.x < 0)
			g_ame->player->current = eval_anim(g_ame->ship_right, t);
		if (g_ame->player->player_pos.y - g_ame->player->next_pos.y < 0)
			g_ame->player->current = eval_anim(g_ame->ship_down, t);
		if (g_ame->player->player_pos.y - g_ame->player->next_pos.y > 0)
			g_ame->player->current = eval_anim(g_ame->ship_up, t);
	}
	else
		update_sprite_pla2(t);
}

void	update_pos(void)
{
	if (g_ame->player->is_moving != 1)
		return ;
	g_ame->player->player_pos = v2(
			g_ame->player->player_pos.x + g_ame->player->dir.x * 2.4,
			g_ame->player->player_pos.y + g_ame->player->dir.y * 2.4);
	if (distance(v2_f(g_ame->player->player_pos.x, g_ame->player->player_pos.y),
			v2_f(g_ame->player->next_pos.x, g_ame->player->next_pos.y)) < 4)
	{
		g_ame->player->player_pos = g_ame->player->next_pos;
		g_ame->player->is_moving = 0;
	}
}

t_color	eval_player(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;	

	if (data.local_pos.x > 0.85 || data.local_pos.x < 0.15
		|| data.local_pos.y > 0.85 || data.local_pos.y < 0.15)
		return (new_color(0, 0, 0, 0));
	if (g_ame->player->is_in_water == 0)
	{
		data.local_pos.x = map(data.local_pos.x, v2_f(0.15, 0.85), v2_f(0, 1));
		data.local_pos.y = map(data.local_pos.y, v2_f(0.15, 0.85), v2_f(0, 1));
	}
	p = v2(
			lerp(0, g_ame->player->current->size->x, data.local_pos.x),
			lerp(0, g_ame->player->current->size->y, data.local_pos.y));
	p.x = clamp(0, g_ame->player->current->size->x, p.x);
	p.y = clamp(0, g_ame->player->current->size->y, p.y);
	out = getpixel(g_ame->player->current, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}

void	update_player(t_rendering_element *elem)
{
	t_vector2_f	feet_pos;
	float		v;

	if ((int)g_ame->time % UPDATE_RATE != 0)
		return ;
	update_pos();
	feet_pos = v2_f(g_ame->player->player_pos.x + elem->element_size.x / 2.0,
			g_ame->player->player_pos.y + elem->element_size.y);
	v = lpnoise(feet_pos.x / g_ame->screen_dim->x,
			feet_pos.y / g_ame->screen_dim->y, v2_f(g_ame->seed, g_ame->seed));
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
		g_ame->player->is_in_water = 1;
	else
		g_ame->player->is_in_water = 0;
	update_sprite_pla();
	elem->element_pos->x = g_ame->player->player_pos.x;
	elem->element_pos->y = g_ame->player->player_pos.y;
}
