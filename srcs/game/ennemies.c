/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:49:48 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include "mmath.h"
#include "utils.h"
#include "random.h"
#include <math.h>



#define UPDATE_RATE 1
#define ENNEMY_MOVE_FRAMES 65.0

void	update_sprite_enn(void)
{
	int		curr_time;
	float	t;

	curr_time = g_ame->time - g_ame->ennemy->start_time;
	t = curr_time / ENNEMY_MOVE_FRAMES;
	if (g_ame->ennemy->is_in_water)
	{
		if (g_ame->ennemy->ennemy_pos.x - g_ame->ennemy->next_pos.x > 0)
			g_ame->ennemy->current = eval_anim(g_ame->ship_left, t);
		if (g_ame->ennemy->ennemy_pos.x - g_ame->ennemy->next_pos.x < 0)
			g_ame->ennemy->current = eval_anim(g_ame->ship_right, t);
		if (g_ame->ennemy->ennemy_pos.y - g_ame->ennemy->next_pos.y < 0)
			g_ame->ennemy->current = eval_anim(g_ame->ship_down, t);
		if (g_ame->ennemy->ennemy_pos.y - g_ame->ennemy->next_pos.y > 0)
			g_ame->player->current = eval_anim(g_ame->ship_up, t);
	}
	else
	{
		if (g_ame->ennemy->ennemy_pos.x - g_ame->ennemy->next_pos.x > 0)
			g_ame->ennemy->current = eval_anim(g_ame->ennemy->anim_lside, t);
		if (g_ame->ennemy->ennemy_pos.x - g_ame->ennemy->next_pos.x < 0)
			g_ame->ennemy->current = eval_anim(g_ame->ennemy->anim_rside, t);
		if (g_ame->ennemy->ennemy_pos.y - g_ame->ennemy->next_pos.y < 0)
			g_ame->ennemy->current = eval_anim(g_ame->ennemy->anim_front, t);
		if (g_ame->ennemy->ennemy_pos.y - g_ame->ennemy->next_pos.y > 0)
			g_ame->ennemy->current = eval_anim(g_ame->ennemy->anim_back, t);
	}
}

void	move_ennemy(t_vector2 direction)
{
	t_vector2	map_pos;

	if (g_ame->ennemy->is_moving == 1)
		return ;
	g_ame->ennemy->next_pos = v2(
			g_ame->ennemy->ennemy_pos.x + direction.x * g_ame->pixel_per_tile,
			g_ame->ennemy->ennemy_pos.y + direction.y * g_ame->pixel_per_tile);
	g_ame->ennemy->dir = direction;
	map_pos = screen_to_map(g_ame->ennemy->next_pos);
	if (g_ame->map[map_pos.y][map_pos.x] == WALL)
		g_ame->ennemy->is_moving = 0;
	else
		g_ame->ennemy->is_moving = 1;
	g_ame->ennemy->start_time = g_ame->time;
}

void	update_pos_ennemy(void)
{
	if (g_ame->ennemy->is_moving != 1)
		return ;
	g_ame->ennemy->ennemy_pos = v2(
		g_ame->ennemy->ennemy_pos.x + g_ame->ennemy->dir.x,
		g_ame->ennemy->ennemy_pos.y + g_ame->ennemy->dir.y);
	if (distance(
		v2_f(g_ame->player->player_pos.x, g_ame->player->player_pos.y),
		v2_f(g_ame->ennemy->ennemy_pos.x, g_ame->ennemy->ennemy_pos.y)) < 5 && g_ame->time > 20)
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
	if (abs(data.global_pos.x - (g_ame->ennemy->ennemy_pos.x + data.element_size.x / 2)) < 2)
		out = new_color(255,0,0,1);
	if (abs(data.global_pos.y - (g_ame->ennemy->ennemy_pos.y + data.element_size.x - 10)) < 2)
		out = new_color(255,0,0,1);
	return (out);
}

void	update_ennemy(t_rendering_element *elem)
{
	t_vector2	pos;
	t_vector2	size;
	float		i;
	float		v;
	t_vector2	feet_pos;

	if (g_ame->ennemy->is_moving != 1)
	{
		i = rnd(&g_ame->ennemy->seed);
		if (i < 0)
		{
			if (i < -0.75)
				move_ennemy(v2(0, -1));
			else
				move_ennemy(v2(0, 1));
		}
		else
		{
			if (i < 0.75)
				move_ennemy(v2(-1, 0));
			else
				move_ennemy(v2(1, 0));
		}
	}
	pos = g_ame->ennemy->ennemy_pos;
	size = elem->element_size;
	update(pos, size, 5);
	update_pos_ennemy();
	feet_pos = v2(g_ame->ennemy->ennemy_pos.x + elem->element_size.x / 2,
		g_ame->ennemy->ennemy_pos.y + elem->element_size.y);
	v = lpnoise(feet_pos.x / g_ame->screen_dim->x, feet_pos.y / g_ame->screen_dim->y, v2_f(g_ame->seed, g_ame->seed)); // Ca ne tile pas avec localpos ???????,
	v = map(v, (t_vector2_f){.x = 0.5, .y = 1},
			(t_vector2_f){.x = 0, .y = 1});
	if (v < SEA_LEVEL)
		g_ame->ennemy->is_in_water = 1;
	else
		g_ame->ennemy->is_in_water = 0;
	update_sprite_enn();
	elem->element_pos->x = g_ame->ennemy->ennemy_pos.x;
	elem->element_pos->y = g_ame->ennemy->ennemy_pos.y;
	pos = g_ame->ennemy->ennemy_pos;
	size.y += 2;
	size.x += 2;
	pos.x -= 1;
	pos.y -= 1;
	update(pos, size, -1);
}
