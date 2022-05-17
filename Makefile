NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLX := -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
	INCLUDES := -I./includes -I/usr/local/include -I./libft -I./ft_printf/includes
else
	INCLUDES := -I./includes -I/usr/include -I./mlx_linux -I./libft -I./ft_printf/includes
	MLX := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

SRCS =	./srcs/images/images.c					\
		./srcs/mmath/mmath.c					\
		./srcs/mmath/mmath2.c					\
		./srcs/mmath/mmath3.c					\
		./srcs/ttypes/ttypes.c					\
		./srcs/ttypes/ttypes2.c					\
		./srcs/ttypes/ttypes3.c					\
		./srcs/random/random_utils.c			\
		./srcs/random/pnoise.c					\
		./srcs/random/frac_brown_motion.c		\
		./srcs/rendering/rendering_chain.c		\
		./srcs/rendering/rendering_chain2.c		\
		./srcs/game/map_parser.c				\
		./srcs/game/init_game.c					\
		./srcs/game/signals_manager.c			\
		./srcs/game/loop.c						\
		./srcs/game/animation.c					\
		./srcs/game/background.c				\
		./srcs/game/rocks.c						\
		./srcs/game/item.c						\
		./srcs/game/exit.c						\
		./srcs/game/counter.c					\
		./srcs/game/sky.c						\
		./srcs/game/player.c					\
		./srcs/game/ennemies.c					\
		./srcs/utils/utils.c					\
		./srcs/main.c

OBJ = ${SRCS:.c=.o}

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) bonus -C ./libft
	cp libft/libft.a .
	$(MAKE) -C ./ft_printf
	cp ft_printf/libftprintf.a .
	$(CC) $(FLAGS) $(OBJ) libft.a libftprintf.a -O3 $(MLX) -o $(NAME)

all: $(NAME)

smallclean:
	$(RM) $(OBJ)

smallfclean: smallclean
	$(RM) $(NAME)

clean: smallclean
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./ft_printf
	$(RM) $(OBJ)

fclean: smallfclean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./ft_printf

re: fclean all

.PHONY = clean fclean all re