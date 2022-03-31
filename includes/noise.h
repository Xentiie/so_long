/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:18:59 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 20:57:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
# define NOISE_H

# include "ttypes.h"

typedef struct s_noise_data
{
	float		gain;
	float		start_freq;
	float		lacunarity;
	int			layers;
	t_vector2_f	scale;
}		t_noise_data;

float	noise2(float x, float y, int *perm);
int		*load_permutation(char *fileName);
float	get_point(int x, int y);

#endif