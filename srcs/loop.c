/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:15:08 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 22:22:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"
#include <stdio.h>

int	i = 0;

int	update_game(void *useless)
{
	useless = NULL;
	update(g_ame->render_img, *(g_ame->screen_size));
	mlx_put_image_to_window(g_ame->mlx, g_ame->mlx_win, g_ame->render_img->img, 0, 0);
	printf("Loop: %d\n", i);
	i++;
	return (1);
}
