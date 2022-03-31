/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 22:21:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include "game.h"
#include "rendering.h"
#include "noise.h"
#include "logger.h"
#include "mmath.h"
#include <stdio.h>

//TODO:	player
//		meilleur graphismes
//		effet visuels
//		ennemies

void	init(t_vector2 *size)
{
	g_ame = malloc(sizeof(t_game));
	if (!g_ame)
		register_error("Memory error !\n");
	g_ame->screen_size = size;
	g_ame->mlx = mlx_init();
	if (!g_ame->mlx)
		register_error("MLX error !\n");
	g_ame->mlx_win = mlx_new_window(g_ame->mlx,
			g_ame->screen_size->x, g_ame->screen_size->y, "so_long");
	if (!g_ame->mlx_win)
		register_error("MLX error !\n");
	g_ame->render_img = new_img(g_ame->mlx, *(g_ame->screen_size));
}

void	register_graphics(t_vector2 size)
{
	add_graphics(&eval_bg, 0, new_v2(0, 0), size);
}

int	main(int argc, char **argv)
{
	t_vector2	size;
	t_tile_type	**map;

	ft_set_logging(MAINCALLS);
	if (argc != 2)
		register_error("Argument error !\n");
	map = parse_map(argv[1], &(size.x), &(size.y));
	size.x *= PIXEL_PER_TILE;
	size.y *= PIXEL_PER_TILE;
	init(&size);
	register_graphics(*(g_ame->screen_size));
	mlx_loop_hook(g_ame->mlx, update_game, NULL);
	mlx_loop(g_ame->mlx);
	return (0);
}
