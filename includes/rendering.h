/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:34:11 by reclaire          #+#    #+#             */
/*   Updated: 2022/04/19 16:28:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "ttypes.h"
# include "images.h"
# include "libft.h"

t_list								*g_rendering_chain;
typedef struct s_rendering_element	t_rendering_element;

typedef struct s_rendering_data
{
	t_vector2_f			local_pos;
	t_vector2			global_pos;
	t_vector2			*element_pos;
	t_vector2			element_size;
	int					element_index;
	t_rendering_element	*self;
}	t_rendering_data;

typedef struct s_rendering_element
{
	t_color						(*eval)(t_rendering_data);
	t_vector2					*element_pos;
	t_vector2					element_size;
	int							layer;
}	t_rendering_element;

t_rendering_element	*add_graphics(t_color (*eval)(t_rendering_data),
						int layer, t_vector2 *pos, t_vector2 size);
void				destroy_graphics(t_rendering_element *elem);
void				update(t_vector2 xy, t_vector2 size, int except_lay);
void				free_graphics(void);
void				update_debug(t_image *img, t_vector2 xy, t_vector2 size);
t_color				get_pixel_at(int x, int y, int *e_lay, int except_lay);

#endif