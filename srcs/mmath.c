/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:06:12 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 20:36:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmath.h"

float	dot_product_2d(float x1, float y1, float x2, float y2)
{
	return (x1 * x2 + y1 * y2);
}

float	lerp(float x, float y, float s)
{
	return (x + s * (y - x));
}

float	smooth_lerp(float x, float y, float s)
{
	return (lerp(x, y, s * s * (3 - 2 * s)));
}

float	inverse_lerp(float a, float b, float value)
{
	return ((value - a) / (b - a));
}

float	map(float v, t_vector2_f from, t_vector2_f to)
{
	float	normal;
	float	tp_max_abs;
	float	to_abs;

	normal = (v - from.x) / (from.y - from.x);
	tp_max_abs = to.y - to.x;
	to_abs = tp_max_abs * normal;
	return (to_abs + to.x);
}
