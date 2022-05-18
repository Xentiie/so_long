/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:26:43 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 16:57:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "ttypes.h"
# include "images.h"
# include "rendering.h"

# define PIXEL_PER_TILE 64
# define SEA_LEVEL 0.6
# define SAND_WIDTH 0.2

typedef struct s_anim
{
	int		count;
	t_image	**sprites;
}	t_anim;

typedef struct s_player
{
	t_vector2	player_pos;
	t_vector2	next_pos;
	t_vector2	dir;
	float		mov_prog;
	int			start_time;
	int			is_moving;
	t_image		*current;
	t_anim		*anim_back;
	t_anim		*anim_front;
	t_anim		*anim_rside;
	t_anim		*anim_lside;
	int			is_in_water;
}	t_player;

typedef struct s_ennemy
{
	t_vector2	ennemy_pos;
	t_vector2	next_pos;
	t_vector2	dir;
	float		mov_prog;
	int			start_time;
	int			is_moving;
	int			seed;
	t_image		*current;
	t_anim		*anim_back;
	t_anim		*anim_front;
	t_anim		*anim_rside;
	t_anim		*anim_lside;
	int			is_in_water;
}	t_ennemy;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	int			seed;
	int			pixel_per_tile;
	t_vector2	*screen_dim;
	t_vector2	*map_dim;
	t_image		*render_img;
	int			time;
	t_tile_type	**map;
	t_anim		*rocks;
	t_anim		*portail;
	t_anim		*ship_up;
	t_anim		*ship_down;
	t_anim		*ship_left;
	t_anim		*ship_right;
	t_image		*portail_curr;
	t_image		**collectibles;
	t_image		*background;
	t_player	*player;
	t_ennemy	*ennemy;
	int			item_count;
	int			item_collected;
	t_vector2	*exit_pos;
	t_vector3_f	light_pos;
	int			mov_counter;
	t_anim		*nums;
}	t_game;

typedef struct s_entity
{
	void				(*f)(t_rendering_element *);
	t_rendering_element	*elem;
}	t_entity;

t_game	*g_ame;

//signals_manager.c

void		error_signal(char	*msg);
void		quit_signal(void);
void		free_anim(t_anim *anim);

//map_parser.c

int			count_chars(char *s, char c);
t_tile_type	parse_c(char c);
void		is_filename_valid(char *str);
t_tile_type	**parse_map(char *file_path, int *size_x, int *size_y);

//background.c

t_color		eval_background(t_rendering_data data);
t_color		eval_background2(t_rendering_data data);

//rocks.c

t_color		eval_rocks(t_rendering_data data);

//loop.c

int			update_game(void *useless);
void		add_entity(void (*f)(t_rendering_element *),
				t_rendering_element *elem);
void		free_entities(void);

//sky.c

int			is_inside(t_vector2_f p);
t_color		eval_sky(t_rendering_data data);
t_color		eval_waterfall(t_rendering_data data);
t_color		eval_ground(t_vector2_f uv);
void		update_waterfall(t_rendering_element *elem);

//player.c

t_color		eval_player(t_rendering_data data);
void		update_player(t_rendering_element *elem);
void		register_movement(t_vector2 direction);

//item.c

t_color		eval_item(t_rendering_data data);

//exit.c

t_color		eval_exit(t_rendering_data data);
void		update_exit(t_rendering_element *elem);

//init_game.c

void		init_game(char *map_path);

//ennemies.c

t_color		eval_ennemy(t_rendering_data data);
void		update_ennemy(t_rendering_element *elem);
void		update_pos_ennemy(void);

//animation.c

t_anim		*create_anim(int count, char *files);
t_image		*eval_anim(t_anim *anim, float t);

//counter.c

void		update_counter(void);
void		init_counter(void);
t_color		eval_count1(t_rendering_data data);
t_color		eval_count2(t_rendering_data data);

//main

t_color		eval_bg(t_rendering_data data);
void		add_rocks(t_vector2 pos);
int			handle_keypress(int keycode, void *useless);
t_color		eval_sky3(t_rendering_data data);

#endif