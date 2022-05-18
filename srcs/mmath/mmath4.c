/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:37:03 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 14:37:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmath.h"
#include <math.h>

t_vector3_f	normalize(t_vector3_f v)
{
	float	mag;

	mag = dot3(v, v);
	if (mag > 0.00001)
		return (v3_f(sqrt(v.x / mag), sqrt(v.y / mag), sqrt(v.z / mag)));
	else
		return (v3_f(0.0, 0.0, 0.0));
}

int	minimum(int a, int b)
{
	return ((a * (a < b)) + (b * (b <= a)));
}

int	is_inside_rectangle(int x, int y, t_vector2 *rectangle_pos,
		t_vector2 rectangle_size)
{
	if (x >= rectangle_pos->x && x <= rectangle_pos->x + rectangle_size.x)
	{
		if (y >= rectangle_pos->y && y <= rectangle_pos->y + rectangle_size.y)
		{
			return (1);
		}
	}
	return (0);
}
