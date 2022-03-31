/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:34:11 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 12:56:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "ttypes.h"
# include "images.h"

typedef struct s_rendering_data
{
	t_vector2	local_pos;
	t_vector2	global_pos;
}	t_rendering_data;

typedef struct s_rendering_element
{
	t_color						(*eval)(t_rendering_data);
	t_vector2					element_pos;
	t_vector2					element_size;
	int							layer;
}	t_rendering_element;

void	add_graphics(t_color (*eval)(t_rendering_data),
			int layer, t_vector2 pos, t_vector2 size);
void	update(t_image *img, t_vector2 screen_size);

#endif