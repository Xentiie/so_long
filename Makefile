NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

MLX := -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
INCLUDES := -I./includes -I/usr/local/include -I./libft -I./ft_printf/includes

SRCS =	./srcs/images/images.c					\
		./srcs/images/images2.c					\
		./srcs/mmath/mmath.c					\
		./srcs/mmath/mmath2.c					\
		./srcs/mmath/mmath3.c					\
		./srcs/mmath/mmath4.c					\
		./srcs/ttypes/ttypes.c					\
		./srcs/ttypes/ttypes2.c					\
		./srcs/ttypes/ttypes3.c					\
		./srcs/random/random_utils.c			\
		./srcs/random/pnoise.c					\
		./srcs/rendering/rendering_chain.c		\
		./srcs/rendering/rendering_chain2.c		\
		./srcs/game/map_parser.c				\
		./srcs/game/map_parser2.c				\
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
		./srcs/game/sky2.c						\
		./srcs/game/player.c					\
		./srcs/game/player2.c					\
		./srcs/game/ennemies.c					\
		./srcs/game/ennemies2.c					\
		./srcs/utils/utils.c					\
		./srcs/main.c							\
		./srcs/main2.c

OBJ = ${SRCS:.c=.o}

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	cp libft/libft.a .
	$(CC) $(FLAGS) $(OBJ) libft.a -O3 $(MLX) -o $(NAME)

all: $(NAME)

smallclean:
	$(RM) $(OBJ)

smallfclean: smallclean
	$(RM) $(NAME)

clean: smallclean
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ)

fclean: smallfclean
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY = clean fclean all re