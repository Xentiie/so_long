/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:32:51 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:52:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include "ttypes.h"

typedef struct s_image {
	void		*img;
	t_vector2	*size;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

unsigned long	create_rgb(int r, int g, int b);
void			putpixel(t_image *data, int x, int y, int color);
t_image			*new_img(void *mlx, t_vector2 size);
t_image			*new_img_file(void *mlx, char *path);
t_color			lerp_color(t_color a, t_color b, float t);

#endif