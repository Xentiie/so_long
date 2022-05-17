/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:59:07 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 00:15:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmath.h"

float	fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	dot2(t_vector2_f a, t_vector2_f b)
{
	return (a.x * b.x + a.y * b.y);
}

float	dot3(t_vector3_f a, t_vector3_f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	frac(float	v)
{
	return(v - ((long)v));
}

float	step(float treshold, float v)
{
	return (v > treshold);
}

int minimum(int a, int b)
{
	return ((a * (a < b)) + (b * (b <= a)));
}