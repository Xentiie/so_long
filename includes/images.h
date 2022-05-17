/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:32:51 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/15 19:03:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include "ttypes.h"
# include "utils.h"

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
void			putpixel(t_image *data, int x, int y, t_color color);
t_image			*new_img(void *mlx, t_vector2 size);
t_image			*new_img_file(void *mlx, char *path);
t_color			lerp_color(t_color a, t_color b, float t);
t_color			new_color(int r, int g, int b, int a);
t_color			getpixel(t_image *data, int x, int y);
void			free_img(t_image	*img);

#endif