/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:26:43 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 22:21:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <mlx.h>
# include "libft.h"
# include "ttypes.h"
# include "images.h"
# include "rendering.h"
# include <stdlib.h>
# include <math.h>

# define PIXEL_PER_TILE 64

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_vector2	*screen_size;
	t_image		*render_img;
	float		delta_time;
}	t_game;

t_game	*g_ame;

void		del_t_game(void *game);
t_tile_type	**parse_map(char *file_path, int *size_x, int *size_y);
char		*read_all_file(int fd, int read_size);
void		register_error(char	*msg);
t_color		eval_bg(t_rendering_data data);
int			update_game(void *useless);
#endif