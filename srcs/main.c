/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
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

void	add_rocks(t_vector2 pos)
{
	t_vector2	*elem_pos;
	t_vector2_f	rock_p;
	int			i;

	i = g_ame->seed;
	if (rnd(&i) > 0.2f)
	{
		rock_p = v2_f(-5 + (int)rnd_range(-4, 7, &i), -5 + (int)rnd_range(-10, 10, &i));
		elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
				pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
		add_graphics(&eval_rocks, 12, elem_pos,
			v2(32, 64));

		rock_p = v2_f(35 + (int)rnd_range(-7, 7, &i), 5 + (int)rnd_range(-10, 10, &i));
		elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
				pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
		add_graphics(&eval_rocks, 12, elem_pos,
			v2(32, 64));
	}
	else
	{
		rock_p = v2_f((int)rnd_range(5, 20, &i), -5 + (int)rnd_range(-10, 10, &i));
		elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
				pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
		add_graphics(&eval_rocks, 12, elem_pos,
			v2(32, 64));
	}
	//rock_p = v2_f(25, 0);
	//elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile + rock_p.x,
	//		pos.y * g_ame->pixel_per_tile - 30 + rock_p.y);
	//add_graphics(&eval_rocks, 4, elem_pos,
	//	v2(32, 64));
	
}

void	setup_tiles(void)
{
	t_vector2	pos;
	t_vector2	*elem_pos;

	pos = v2(0,0);
	while (pos.y < g_ame->map_dim->y)
	{
		//add_graphics(&eval_sky, 2, pv2(0, pos.y * g_ame->pixel_per_tile),
		//	v2(g_ame->pixel_per_tile, g_ame->pixel_per_tile));
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
			{
				elem_pos = pv2((pos.x + 1) * g_ame->pixel_per_tile,
						pos.y * g_ame->pixel_per_tile - 30);
				add_graphics(&eval_item, 4, elem_pos,
					v2(g_ame->pixel_per_tile - 1, g_ame->pixel_per_tile - 1));
			}
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
}

t_color	eval_bg(t_rendering_data data)
{
    t_color		out;
	t_vector2	p;
    t_image     *img;

    img = g_ame->background;
	p = v2(lerp(0, img->size->x, data.local_pos.x), lerp(0, img->size->y, data.local_pos.y));
	out = getpixel(img, p.x, p.y);
	return (out);
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

int	handle_keypress(int keycode, void *useless)
{
	useless = useless;
#ifdef __linux__
	if (keycode == 65307)
		quit_signal();
	if (keycode == 122)
		register_movement(v2(0, -1));
	if (keycode == 113)
		register_movement(v2(-1, 0));
	if (keycode == 115)
		register_movement(v2(0, 1));
	if (keycode == 100)
		register_movement(v2(1, 0));
#endif
#ifdef __APPLE__
	if (keycode == 65307)
		quit_signal();
	if (keycode == 13)
		register_movement(v2(0, -1));
	if (keycode == 0)
		register_movement(v2(-1, 0));
	if (keycode == 1)
		register_movement(v2(0, 1));
	if (keycode == 2)
		register_movement(v2(1, 0));
#endif
	return (0);
}

t_color	eval_sky3(t_rendering_data data)
{
	t_vector2_f	global_uv;
	float		v;

	global_uv = v2_f((float)data.global_pos.x / g_ame->screen_dim->x,
			(float)data.global_pos.y / g_ame->screen_dim->y);
	v = fabs(lpnoise(global_uv.x * 2 + g_ame->time / 200.0, global_uv.y, v2_f(g_ame->seed, g_ame->seed)));
	if (v > 0.91)
	{
		return (new_color(255 / v / 1.1, 255 / v / 1.1, 255 / v / 1.1, 1));
	}
	return (new_color(30, 160, 250, 1));
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_signal("Argument error !\n");
	init_game(argv[1]);
	g_ame->rocks = create_anim(3, "files/rock");
	init_noise();
	
	add_graphics(&eval_bg, 1, pv2(0, 0), *g_ame->screen_dim);
	add_graphics(&eval_sky3, 0, pv2(0, 0), v2(g_ame->screen_dim->x, g_ame->screen_dim->y / 2));


	setup_tiles();
	setup_entites();
	setup_bg();
	mlx_put_image_to_window(g_ame->mlx, g_ame->mlx_win,
		g_ame->render_img->img, 0, 0);
	mlx_key_hook(g_ame->mlx_win, handle_keypress, NULL);
	mlx_loop_hook(g_ame->mlx, &update_game, g_ame);
	mlx_loop(g_ame->mlx);
}
