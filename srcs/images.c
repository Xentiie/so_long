/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:37:23 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 19:41:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_image	*new_img(void *mlx, t_vector2 size)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	img->img = mlx_new_image(mlx, size.x, size.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	putpixel(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_image	*new_img_file(void *mlx, char *path)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	img->size = malloc(sizeof(t_vector2));
	img->img = mlx_xpm_file_to_image(mlx, path,
			&(img->size->x), &(img->size->y));
	return (img);
}

t_color	lerp_color(t_color a, t_color b, float t)
{
	t_color	out;

	out = (t_color){
		.r = a.r + (b.r - a.r) * t,
		.g = a.g + (b.g - a.g) * t,
		.b = a.b + (b.b - a.b) * t,
		.a = a.a + (b.a - a.a) * t};
	return (out);
}
