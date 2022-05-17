/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttypes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:47:19 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:48:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ttypes.h"
#include <stdlib.h>

t_vector4_f	v4_f(float x, float y, float z, float w)
{
	return ((t_vector4_f){.x = x, .y = y, .z = z, .w = w});
}

t_vector2	*pv2(int x, int y)
{
	t_vector2	*p;

	p = malloc(sizeof(t_vector2));
	p->x = x;
	p->y = y;
	return (p);
}

t_vector2_f	*pv2_f(float x, float y)
{
	t_vector2_f	*p;

	p = malloc(sizeof(t_vector2_f));
	p->x = x;
	p->y = y;
	return (p);
}

t_vector3	*pv3(int x, int y, int z)
{
	t_vector3	*p;

	p = malloc(sizeof(t_vector3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}
