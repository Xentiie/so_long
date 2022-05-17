/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:35:40 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/06 12:20:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "images.h"
#include "mmath.h"

t_anim	*create_anim(int count, char *files)
{
	int		i;
	char	*filename;
	char	*tmp;
	t_anim	*out;

	out = mmalloc(sizeof(t_anim));
	out->sprites = mmalloc(sizeof(t_image *) * count);
	i = 0;
	while (i < count)
	{
		filename = mmalloc(sizeof(char)
				* (ft_strlen(files) + ft_magnitude(count) + 5));
		ft_bzero(filename, ft_strlen(files) + ft_magnitude(count));
		ft_strcat(filename, files);
		tmp = ft_itoa(i + 1);
		ft_strcat(filename, tmp);
		ft_strcat(filename, ".xpm");
		out->sprites[i] = new_img_file(g_ame->mlx, filename);
		free(tmp);
		free(filename);
		i++;
	}
	out->count = count;
	return (out);
}

t_image	*eval_anim(t_anim *anim, float t)
{
	t = clampf(0, 0.99, t);
	return (anim->sprites[(int)(t * anim->count)]);
}
