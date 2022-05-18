/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 16:50:49 by reclaire         ###   ########.fr       */
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

void	setup_tiles(void)
{
	t_vector2	pos;

	pos = v2(0, 0);
	while (pos.y < g_ame->map_dim->y)
	{
		while (pos.x < g_ame->map_dim->x)
		{
			if (pos.x == 0 || pos.x == g_ame->map_dim->x - 2
				|| pos.y == 0 || pos.y == g_ame->map_dim->y - 1)
			{
				pos.x++;
				continue ;
			}
			if (g_ame->map[pos.y][pos.x] == WALL)
				add_rocks(pos);
			if (g_ame->map[pos.y][pos.x] == ITEM)
				add_graphics(&eval_item, 4,
					pv2((pos.x + 1) * g_ame->pixel_per_tile,
						pos.y * g_ame->pixel_per_tile - 30),
					v2(g_ame->pixel_per_tile - 1, g_ame->pixel_per_tile - 1));
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
}

void	setup_bg(void)
{
	t_vector2			pos;
	t_rendering_data	data;

	pos = v2(0, 0);
	g_ame->background = new_img(g_ame->mlx, *g_ame->screen_dim);
	while (pos.y < g_ame->screen_dim->y)
	{
		while (pos.x < g_ame->screen_dim->x)
		{
			data = (t_rendering_data){
				.element_index = 0,
				.element_pos = pv2(0, 0),
				.element_size = *g_ame->screen_dim,
				.global_pos = pos,
				.local_pos = v2_f(0, 0),
				.self = NULL
			};
			putpixel(g_ame->background, pos.x, pos.y, eval_sky(data));
			free(data.element_pos);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
}

void	setup_entities2(void)
{
	add_entity(&update_waterfall,
		add_graphics(&eval_waterfall, 0,
			pv2(0, g_ame->screen_dim->y / 2),
			v2(g_ame->screen_dim->x, g_ame->screen_dim->y / 2)));
	g_ame->ennemy->ennemy_pos = g_ame->player->player_pos;
	add_entity(&update_ennemy,
		add_graphics(&eval_ennemy, 15,
			pv2(g_ame->ennemy->ennemy_pos.x,
				g_ame->ennemy->ennemy_pos.y),
			v2(g_ame->pixel_per_tile, g_ame->pixel_per_tile)));
}

void	setup_entites(void)
{
	t_vector2			pos;

	pos = v2(0, 0);
	while (pos.y < g_ame->map_dim->y)
	{
		while (pos.x < g_ame->map_dim->x)
		{
			if (g_ame->map[pos.y][pos.x] == SPAWN)
			{
				g_ame->player->player_pos = v2((pos.x + 1)
						* g_ame->pixel_per_tile,
						pos.y * g_ame->pixel_per_tile - 30);
				add_entity(&update_player, add_graphics(&eval_player, 10,
						pv2(g_ame->player->player_pos.x,
							g_ame->player->player_pos.y),
						v2(g_ame->pixel_per_tile, g_ame->pixel_per_tile)));
			}
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	setup_entities2();
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_signal("Argument error !\n");
	init_game(argv[1]);
	g_ame->rocks = create_anim(3, "files/rock");
	init_noise();
	add_graphics(&eval_bg, 1, pv2(0, 0), *g_ame->screen_dim);
	add_graphics(&eval_sky3, 0, pv2(0, 0),
		v2(g_ame->screen_dim->x, g_ame->screen_dim->y / 2));
	setup_tiles();
	setup_entites();
	setup_bg();
	mlx_put_image_to_window(g_ame->mlx, g_ame->mlx_win,
		g_ame->render_img->img, 0, 0);
	mlx_key_hook(g_ame->mlx_win, handle_keypress, NULL);
	mlx_loop_hook(g_ame->mlx, &update_game, g_ame);
	mlx_loop(g_ame->mlx);
}
