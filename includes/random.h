/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:18:59 by reclaire          #+#    #+#             */
/*   Updated: 2022/04/07 17:22:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include "ttypes.h"

typedef struct s_noise_data
{
	t_vector2_f	scale;
	float		base_roughness;
	float		rougness;
	float		persistence;
	int			layers;
}		t_noise_data;

int	*g_p;

void	init_noise(void);
float	pnoise(float x, float y);
float	grad2( int hash, float x, float y);
float	lpnoise(float x, float y, t_vector2_f offset);
float	lpnoise_custom(float x, float y, t_noise_data data);
float	rnd(int *seed);
float	rnd_range(float min, float max, int *seed);
float	fbm(t_vector2_f _st);
void	free_perms(void);

#endif