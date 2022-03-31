/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:06:20 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 20:36:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMATH_H
# define MMATH_H

# include "ttypes.h"

float	dot_product_2d(float x1, float y1, float x2, float y2);
float	lerp(float x, float y, float s);
float	smooth_lerp(float x, float y, float s);
float	inverse_lerp(float a, float b, float value);
float	map(float v, t_vector2_f from, t_vector2_f to);
float	fade(float t);

#endif