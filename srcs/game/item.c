/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:05:09 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:05:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ttypes.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

void	collect_item(t_rendering_data data)
{
	destroy_graphics(data.self);
	g_ame->item_collected++;
	if (g_ame->item_collected == g_ame->item_count)
		add_entity(&update_exit, add_graphics(&eval_exit,
				6, g_ame->exit_pos, v2(PIXEL_PER_TILE, PIXEL_PER_TILE)));
}

t_color	eval_item(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;
	int			index;
	t_vector2_f	pos;
	t_image		*img;

	if (g_ame->player->player_pos.x == data.element_pos->x
		&& g_ame->player->player_pos.y == data.element_pos->y)
		collect_item(data);
	pos.x = data.element_pos->x / (float)g_ame->screen_dim->x;
	pos.y = data.element_pos->y / (float)g_ame->screen_dim->y;
	index = clamp(0, 14, (int)map(pnoise(pos.x, pos.y),
				v2_f(-1, 1), v2_f(0, 15)));
	img = g_ame->collectibles[index];
	p = v2(lerp(0, img->size->x, data.local_pos.x),
			lerp(0, img->size->y, data.local_pos.y));
	p.x = minimum(p.x, 15);
	p.y = minimum(p.y, 15);
	out = getpixel(img, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}
