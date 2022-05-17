/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttypes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:44:30 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:51:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ttypes.h"

t_vector2	v2(int x, int y)
{
	return ((t_vector2){.x = x, .y = y});
}

t_vector2_f	v2_f(float x, float y)
{
	return ((t_vector2_f){.x = x, .y = y});
}

t_vector3	v3(int x, int y, int z)
{
	return ((t_vector3){.x = x, .y = y, .z = z});
}

t_vector3_f	v3_f(float x, float y, float z)
{
	return ((t_vector3_f){.x = x, .y = y, .z = z});
}

t_vector4	v4(int x, int y, int z, int w)
{
	return ((t_vector4){.x = x, .y = y, .z = z, .w = w});
}
