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

FLAGS = -Wall -Wextra -Werror

NAME = cub3D

HEADER = include/cub3d.h

SRC = 	src/ft_check_map.c src/ft_draw_3d.c src/ft_draw_sprite.c src/ft_exit.c \
	src/ft_find_player.c src/ft_find_sprites.c src/ft_get_resolution.c \
	src/ft_init_info.c src/ft_keypress.c src/ft_parse_file.c \
	src/ft_parse_map.c src/ft_put_ray.c src/main.c gnl/get_next_line.c \
	gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C minilibx-linux
	mv minilibx-linux/libmlx_Linux.a .
	make -C libft
	mv libft/libft.a .
	gcc $(FLAGS) -g -o $(NAME) $(SRC) libmlx_Linux.a libft.a -L minilibx-linux -lmlx -lXext -lX11 -lm

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME) libmlx_Linux.a libft.a cub3d.bmp

re: fclean all

bonus: all

leak: valgrind --leak-check=full ./cub3D map.cub

.PHONY: all clean fclean re

