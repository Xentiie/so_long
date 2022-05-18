/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:58:10 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:07:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "game.h"
#include "random.h"

void	free_map(void)
{
	int	y;

	y = 0;
	while (y < g_ame->map_dim->y)
	{
		free(g_ame->map[y]);
		y++;
	}
	free(g_ame->map);
	free(g_ame->map_dim);
	free(g_ame->screen_dim);
}

void	quit_signal2(void)
{
	int	i;

	free_img(g_ame->render_img);
	free_img(g_ame->background);
	i = 0;
	while (i < 15)
		free_img(g_ame->collectibles[i++]);
	free(g_ame->collectibles);
	free_anim(g_ame->player->anim_back);
	free_anim(g_ame->player->anim_front);
	free_anim(g_ame->player->anim_lside);
	free_anim(g_ame->player->anim_rside);
	free(g_ame->player);
	free_anim(g_ame->ennemy->anim_back);
	free_anim(g_ame->ennemy->anim_front);
	free_anim(g_ame->ennemy->anim_lside);
	free_anim(g_ame->ennemy->anim_rside);
}

void	free_anim(t_anim *anim)
{
	int	i;

	i = 0;
	while (i < anim->count)
		free_img(anim->sprites[i++]);
	free(anim->sprites);
	free(anim);
}

//	mlx_loop_end(g_ame->mlx);
//	mlx_destroy_display(g_ame->mlx);
//free(g_ame->exit_pos); est free dans free_graphics
void	quit_signal(void)
{
	free_graphics();
	quit_signal2();
	free(g_ame->ennemy);
	free_anim(g_ame->nums);
	free_anim(g_ame->ship_down);
	free_anim(g_ame->ship_left);
	free_anim(g_ame->ship_right);
	free_anim(g_ame->ship_up);
	free_anim(g_ame->portail);
	free_anim(g_ame->rocks);
	free_map();
	free_entities();
	free_perms();
	mlx_clear_window(g_ame->mlx, g_ame->mlx_win);
	mlx_destroy_window(g_ame->mlx, g_ame->mlx_win);
	free(g_ame->mlx);
	free(g_ame);
	exit(EXIT_SUCCESS);
}

void	error_signal(char	*msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
