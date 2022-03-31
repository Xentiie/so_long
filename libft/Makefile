# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/03/17 14:19:08 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	libft.a	
SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c	\
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_str_is_alpha.c \
			ft_str_is_numeric.c \
			ft_str_is_lowercase.c \
			ft_str_is_uppercase.c \
			ft_str_is_printable.c \
			ft_strupcase.c \
			ft_strlowcase.c \
			ft_strcapitalize.c \
			ft_strcmp.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strstr.c \
			ft_pow.c \
			ft_sqrt.c \
			ft_is_prime.c \
			ft_find_next_prime.c \
			ft_range.c \
			ft_nrange.c \
			ft_checkbase.c \
			ft_getindex.c \
			ft_atoi_base.c \
			ft_magnitude.c \
			ft_uitoa.c

SRCS_B = 	ft_lstnew.c \
			ft_lstsize.c \
			ft_lstadd_front.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJS	=	${SRCS:.c=.o}
OBJS_B	=	${SRCS_B:.c=.o}
HEADER  =	./
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

.c.o:	
			$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)
				
all:		$(NAME)

clean:		
			$(RM) $(OBJS) $(OBJS_B)
			
fclean:		clean
			$(RM) $(NAME)

bonus:		$(NAME) $(OBJS_B)
			ar rc $(NAME) $(OBJS_B)

re:			fclean all clean

.PHONY:		fclean all clean