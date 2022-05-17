
LIBFT = ../libft
NAME = libftprintf.a
RM = rm -rf

SRCS	=	./srcs/handle_c.c \
			./srcs/handle_d.c \
			./srcs/handle_i.c \
			./srcs/handle_p.c \
			./srcs/handle_s.c \
			./srcs/handle_u.c \
			./srcs/handle_uX.c \
			./srcs/handle_x.c \
			./srcs/ft_printf.c

CC = gcc

FLAGS := -c -Wall -Wextra -Werror
INCLUDES := -I./includes -I$(LIBFT)

OBJS = 		handle_c.o \
			handle_d.o \
			handle_i.o \
			handle_p.o \
			handle_s.o \
			handle_u.o \
			handle_uX.o \
			handle_x.o \
			ft_printf.o

$(NAME) :
	$(MAKE) bonus -C $(LIBFT)
	cp $(LIBFT)/libft.a $(NAME)
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

main:	$(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) libftprintf.a main.c

all : $(NAME)

clean :
	$(MAKE) clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

re : fclean all