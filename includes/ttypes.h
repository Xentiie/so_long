/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttypes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:25:21 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:48:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTYPES_H
# define TTYPES_H

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_vector2_f
{
	float	x;
	float	y;
}				t_vector2_f;

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
}				t_vector3;

typedef struct s_vector3_f
{
	float	x;
	float	y;
	float	z;
}				t_vector3_f;

typedef struct s_vector4
{
	int	x;
	int	y;
	int	z;
	int	w;
}				t_vector4;

typedef struct s_vector4_f
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vector4_f;

typedef enum e_tile_type
{
	EMPTY,
	WALL,
	ITEM,
	EXIT,
	SPAWN
}	t_tile_type;

t_vector2	new_v2(int x, int y);
t_vector2_f	new_v2_f(float x, float y);
t_vector3	new_v3(int x, int y, int z);
t_vector3_f	new_v3_f(float x, float y, float z);
t_vector4	new_v4(int x, int y, int z, int w);
t_vector4_f	new_v4_f(float x, float y, float z, float w);

#endif