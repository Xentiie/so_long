/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rocks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:25 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "random.h"
#include "mmath.h"
#include <math.h>

#include <stdlib.h>

t_color	eval_rocks(t_rendering_data data)
{
	t_color		out;
	t_vector2	p;
	t_image		*curr;
	float		f;

	f = fabs(frac(sin(dot2(v2_f(data.element_pos->x, data.element_pos->y), v2_f(12.9898, 78.233))) * 43758.5453));
	if (f >= 0.0 && f < 0.33)
		curr = g_ame->rocks->sprites[0];
	else if (f >= 0.33 && f < 0.66)
		curr = g_ame->rocks->sprites[1];
	else
		curr = g_ame->rocks->sprites[2];
	p = v2(lerp(0, curr->size->x - 1, data.local_pos.x), lerp(0, curr->size->y, data.local_pos.y));
	//if (data.local_pos.y > 0.9)
	//	return (check_foam(data, curr));
	out = getpixel(curr, p.x, p.y);
	out.a = lerp(1, 0, inverse_lerp(0, 1, out.a));
	return (out);
}
