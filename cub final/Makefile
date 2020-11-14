# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 14:00:21 by jrosemar          #+#    #+#              #
#    Updated: 2020/10/27 14:00:23 by jrosemar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall

NAME = cub3D

INCLIB=../LIBFT

HEADER = include/cub3d.h

SRC = src/*.c GNL/*.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	make -C LIBFT
#	cp LIBFT/libft.a .
	gcc $(FLAGS) -g -o $(NAME) $(SRC) LIBFT/libft.a -L minilibx-linux -lmlx -lXext -lX11 -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all



