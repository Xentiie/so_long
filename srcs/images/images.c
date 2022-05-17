/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:37:23 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include <mlx.h>
#include <stdlib.h>


#include "ft_printf.h"
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

	hex = (((col.a & 0xff) << 24) + ((col.r & 0xff) << 16) + ((col.g & 0xff) << 8) + (col.b & 0xff));
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

t_color	lerp_color(t_color a, t_color b, float t)
{
	t_color	out;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	out = (t_color){
		.r = a.r + (b.r - a.r) * t,
		.g = a.g + (b.g - a.g) * t,
		.b = a.b + (b.b - a.b) * t,
		.a = a.a + (b.a - a.a) * t};
	return (out);
}

t_color			new_color(int r, int g, int b, int a)
{
	return ((t_color){.r = r, .g = g, .b = b, .a = a});
}

void			free_img(t_image	*img)
{
	mlx_destroy_image(g_ame->mlx, img->img);
	free(img->size);
	free(img);
}
