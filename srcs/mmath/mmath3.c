/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:29:00 by reclaire          #+#    #+#             */
/*   Updated: 2022/04/06 17:38:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmath.h"
#include <math.h>

float	distance(t_vector2_f p1, t_vector2_f p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)));
}

int		wrap(int n, int min, int max)
{
	return (min + (n - min) % (max - min));
}

float	clampf(float min, float max, float v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}

int	clamp(int min, int max, int v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}

t_vector2_f	lerp_v2(t_vector2_f v_1, t_vector2_f v_2, float t)
{
	return (v2_f(
		lerp(v_1.x, v_2.x, t),
		lerp(v_1.y, v_2.y, t)
	));
}

t_vector3_f normalize(t_vector3_f v)
{
	float mag;

	mag = dot3(v, v);
	if (mag > 0.00001)
		return (v3_f(sqrt(v.x / mag), sqrt(v.y / mag), sqrt(v.z / mag)));
	else
		return (v3_f(0.0, 0.0, 0.0));
}
