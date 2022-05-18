/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:38:09 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:02:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include "game.h"
#include "rendering.h"
#include "random.h"
#include "mmath.h"

#include <stdlib.h>
#include <mlx.h>

void	init2(char *map_path)
{
	t_vector2	*map_dim;
	t_vector2	*screen_dim;

	map_dim = pv2(0, 0);
	g_ame = mmalloc(sizeof(t_game));
	if (!g_ame)
		error_signal("Memory error !\n");
	g_ame->item_count = 0;
	g_ame->map = parse_map(map_path, &(map_dim->x), &(map_dim->y));
	g_ame->item_collected = 0;
	g_ame->mlx = mlx_init();
	if (!g_ame->mlx)
		error_signal("MLX error !\n");
	g_ame->pixel_per_tile = PIXEL_PER_TILE;
	if (map_dim->x * PIXEL_PER_TILE > 1920)
		g_ame->pixel_per_tile = minimum(1920 / map_dim->x,
				g_ame->pixel_per_tile);
	if (map_dim->y * PIXEL_PER_TILE > 1080)
		g_ame->pixel_per_tile = minimum(1080 / map_dim->y,
				g_ame->pixel_per_tile);
	screen_dim = pv2(map_dim->x * g_ame->pixel_per_tile
			+ g_ame->pixel_per_tile * 2,
			map_dim->y * g_ame->pixel_per_tile);
	g_ame->map_dim = map_dim;
	g_ame->screen_dim = screen_dim;
}

void	init3(void)
{
	int		i;
	char	*filename;
	char	*tmp;

	g_ame->ship_down = create_anim(2, "files/ship/ship_down");
	g_ame->ship_up = create_anim(2, "files/ship/ship_up");
	g_ame->ship_right = create_anim(2, "files/ship/ship_right");
	g_ame->ship_left = create_anim(2, "files/ship/ship_left");
	g_ame->mov_counter = 0;
	g_ame->nums = create_anim(10, "files/num/num");
	g_ame->collectibles = mmalloc(sizeof(t_image *) * 15);
	i = 0;
	while (i < 15)
	{
		filename = mmalloc(sizeof(char) * 22);
		ft_bzero(filename, 22);
		ft_strcat(filename, "files/objets/Q-");
		tmp = ft_itoa(i + 1);
		ft_strcat(filename, tmp);
		ft_strcat(filename, ".xpm");
		(g_ame->collectibles)[i] = new_img_file(g_ame->mlx, filename);
		free(tmp);
		free(filename);
		i++;
	}
}

void	init4(void)
{
	g_ame->ennemy = mmalloc(sizeof(t_ennemy));
	g_ame->ennemy->mov_prog = 0;
	g_ame->ennemy->start_time = 0;
	g_ame->ennemy->is_moving = 0;
	g_ame->ennemy->ennemy_pos = v2(0, 0);
	g_ame->ennemy->next_pos = v2(0, 0);
	g_ame->ennemy->seed = g_ame->seed;
	g_ame->ennemy->anim_back = create_anim(4, "files/pirate/pirate_back");
	g_ame->ennemy->anim_rside = create_anim(4, "files/pirate/pirate_side");
	g_ame->ennemy->anim_front = create_anim(4, "files/pirate/pirate_front");
	g_ame->ennemy->anim_lside = create_anim(4, "files/pirate/pirate_lside");
	g_ame->ennemy->current = g_ame->ennemy->anim_front->sprites[0];
}

void	init5(void)
{
	g_ame->player->player_pos = v2(0, 0);
	g_ame->player->next_pos = v2(0, 0);
	g_ame->player->anim_back = create_anim(4, "files/player/player_back");
	g_ame->player->anim_rside = create_anim(4, "files/player/player_side");
	g_ame->player->anim_front = create_anim(4, "files/player/player_front");
	g_ame->player->anim_lside = create_anim(4, "files/player/player_rside");
}

void	init_game(char *map_path)
{
	init2(map_path);
	g_ame->mlx_win = mlx_new_window(g_ame->mlx,
			g_ame->screen_dim->x, g_ame->screen_dim->y, "so_long");
	if (!g_ame->mlx_win)
		error_signal("MLX error !\n");
	g_ame->render_img = new_img(g_ame->mlx, *(g_ame->screen_dim));
	g_ame->time = 0;
	g_ame->seed = dot2(v2_f(g_ame->screen_dim->x, g_ame->screen_dim->y),
			v2_f(12.54, 51.15)) * 10;
	g_ame->player = mmalloc(sizeof(t_player));
	g_ame->player->mov_prog = 0;
	g_ame->player->start_time = 0;
	g_ame->player->is_moving = 0;
	g_ame->player->is_in_water = 0;
	init5();
	g_ame->player->current = g_ame->player->anim_front->sprites[0];
	g_ame->portail = create_anim(5, "files/portail/portail");
	g_ame->portail_curr = g_ame->portail->sprites[0];
	init3();
	init4();
	init_counter();
}
