/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:06:20 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 14:49:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMATH_H
# define MMATH_H

# include "ttypes.h"

float	    dot_product_2d(float x1, float y1, float x2, float y2);
float	    lerp(float x, float y, float s);
float	    smooth_lerp(float x, float y, float s);
float	    inverse_lerp(float a, float b, float value);
float	    map(float v, t_vector2_f from, t_vector2_f to);
float	    fade(float t);
float	    dot2(t_vector2_f a, t_vector2_f b);
float   	dot3(t_vector3_f a, t_vector3_f b);
float	    frac(float v);
float	    step(float treshold, float v);
int		    minimum(int a, int b);
float	    distance(t_vector2_f p1, t_vector2_f p2);
int		    wrap(int n, int min, int max);
float	    clampf(float min, float max, float v);
int	        clamp(int min, int max, int v);
t_vector2_f	lerp_v2(t_vector2_f v_1, t_vector2_f v_2, float t);
t_vector3_f normalize(t_vector3_f v);
int	        is_inside_rectangle(int x, int y, t_vector2 *rectangle_pos,
		        t_vector2 rectangle_size);

#endif