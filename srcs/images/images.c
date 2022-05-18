/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:37:23 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 16:42:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include <mlx.h>
#include <stdlib.h>
#include "game.h"
#include "mmath.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_image	*new_img(void *mlx, t_vector2 size)
{
	t_image	*img;

	img = mmalloc(sizeof(t_image));
	img->img = mlx_new_image(mlx, size.x, size.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->size = pv2(size.x, size.y);
	return (img);
}

void	putpixel(t_image *data, int x, int y, t_color col)
{
	char	*dst;
	int		hex;

	if (x < 0 || x >= data->size->x || y < 0 || y >= data->size->y)
		return ;
	hex = (((col.a & 0xff) << 24) + ((col.r & 0xff) << 16)
			+ ((col.g & 0xff) << 8) + (col.b & 0xff));
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = hex;
}

t_color	getpixel(t_image *data, int x, int y)
{
	int				pixel;
	t_color			rgb;
	char			*loc;

	loc = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	pixel = *(unsigned int *)loc;
	rgb.a = ((pixel >> 24) & 0xFF);
	rgb.r = ((pixel >> 16) & 0xFF);
	rgb.g = ((pixel >> 8) & 0xFF);
	rgb.b = ((pixel) & 0xFF);
	return (rgb);
}

t_image	*new_img_file(void *mlx, char *path)
{
	t_image	*img;

	img = mmalloc(sizeof(t_image));
	img->size = mmalloc(sizeof(t_vector2));
	img->img = mlx_xpm_file_to_image(mlx, path,
			&(img->size->x), &(img->size->y));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}
