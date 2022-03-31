NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I/usr/local/include -I./libft -I./ft_printf/includes

MLX = -L/usr/local/lib -lmlx

SRCS =	./srcs/main.c \
		./srcs/images.c \
		./srcs/game.c \
		./srcs/map_parser.c \
		./srcs/noise.c \
		./srcs/mmath.c \
		./srcs/mmath2.c \
		./srcs/perlin_noise.c \
		./srcs/rendering_chain.c \
		./srcs/errormanager.c \
		./srcs/ttypes.c \
		./srcs/ttypes2.c \
		./srcs/background.c \
		./srcs/loop.c

OBJ = ${SRCS:.c=.o}

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) bonus -C ./libft
	cp libft/libft.a .
	$(MAKE) -C ./ft_printf
	cp ft_printf/libftprintf.a .
	$(CC) $(FLAGS) $(OBJ) libft.a libftprintf.a $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./ft_printf
	rm -rf $(OBJ)

fclean:
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./ft_printf
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY = clean fclean all re