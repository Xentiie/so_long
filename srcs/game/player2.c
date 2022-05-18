/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:39 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 15:10:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include "mmath.h"
#include "utils.h"
#include "random.h"
#include <math.h>

#include <stdlib.h>

void	register_movement(t_vector2 direction)
{
	t_vector2	map_pos;

	if (g_ame->player->is_moving == 1)
		return ;
	g_ame->player->next_pos = v2(g_ame->player->player_pos.x
			+ direction.x * g_ame->pixel_per_tile,
			g_ame->player->player_pos.y + direction.y
			* g_ame->pixel_per_tile);
	map_pos = screen_to_map(g_ame->player->next_pos);
	if (g_ame->map[map_pos.y][map_pos.x] == WALL)
		g_ame->player->is_moving = 0;
	else
	{
		g_ame->player->is_moving = 1;
		g_ame->mov_counter++;
	}
	g_ame->player->dir = direction;
	g_ame->player->start_time = g_ame->time;
}
