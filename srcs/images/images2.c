/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:55:39 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 14:55:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "images.h"
#include "game.h"

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

t_color	new_color(int r, int g, int b, int a)
{
	return ((t_color){.r = r, .g = g, .b = b, .a = a});
}

void	free_img(t_image	*img)
{
	mlx_destroy_image(g_ame->mlx, img->img);
	free(img->size);
	free(img);
}
