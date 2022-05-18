/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:15:08 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:05:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "rendering.h"

#include <stdlib.h>
#include <mlx.h>

static t_list	*g_entities;

void	add_entity(void (*f)(t_rendering_element *), t_rendering_element *elem)
{
	t_list		*new;
	t_entity	*entity;

	entity = mmalloc(sizeof(t_entity));
	entity->elem = elem;
	entity->f = f;
	new = ft_lstnew(entity);
	ft_lstadd_back(&g_entities, new);
}

void	destroy_entity(void *data)
{
	free(data);
}

void	free_entities(void)
{
	ft_lstclear(&g_entities, &destroy_entity);
}

void	update_entity(void *content)
{
	t_entity	*entity;

	entity = (t_entity *)content;
	entity->f(entity->elem);
}

int	update_game(void	*p_game)
{
	t_game	*game;

	game = (t_game *)p_game;
	ft_lstiter(g_entities, &update_entity);
	update(v2(0, 0), *g_ame->screen_dim, -1);
	mlx_put_image_to_window(game->mlx,
		game->mlx_win, game->render_img->img, 0, 0);
	game->time++;
	return (1);
}
