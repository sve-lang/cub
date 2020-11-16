/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:46:35 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 21:57:01 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			ft_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void			ft_init_player(t_player *player, char c, double x, double y)
{
	if (c == 'N')
		player->corner = M_PI / 2;
	if (c == 'W')
		player->corner = M_PI;
	if (c == 'E')
		player->corner = 0.00;
	if (c == 'S')
		player->corner = 3 * M_PI / 2;
	player->x = x + SIZE / 2;
	player->y = y + SIZE / 2;
}

t_player		ft_find_player(t_info *arg)
{
	int			n;
	int			m;
	int			x;
	int			y;
	t_player	player;

	x = 0;
	y = 0;
	m = -1;
	while (++m < arg->mp)
	{
		n = 0;
		x = 0;
		while (arg->map[m][n] != '\0')
		{
			if (arg->map[m][n] == 'N' || arg->map[m][n] == 'W' ||
			arg->map[m][n] == 'E' || arg->map[m][n] == 'S')
				ft_init_player(&player, arg->map[m][n], (double)x,
				(double)y);
			n++;
			x = x + SIZE;
		}
		y = y + SIZE;
	}
	return (player);
}

void			ft_fill_bmp(char *bmp, int num, int size, t_info *arg)
{
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0], "BM", 2);
	ft_memcpy(&bmp[2], &size, 4);
	ft_memcpy(&bmp[10], &num, 4);
	num = 40;
	ft_memcpy(&bmp[14], &num, 4);
	ft_memcpy(&bmp[18], &arg->res[0], 4);
	num = -arg->res[1];
	ft_memcpy(&bmp[22], &num, 4);
	num = 1;
	ft_memcpy(&bmp[26], &num, 2);
	num = 32;
	ft_memcpy(&bmp[28], &num, 2);
	ft_memcpy(&bmp[54], arg->cub.addr, (size - 54));
}

void			ft_create_bmp(t_info *arg)
{
	int			size;
	char		*bmp;
	int			fd;

	size = (arg->res[0] * arg->res[1] * 4) + 54;
	if (!(bmp = (char *)malloc(size)))
		ft_error("Error! Failed to allocate memory.\n", arg, 65307);
	ft_fill_bmp(bmp, 54, size, arg);
	fd = open("cub.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, bmp, size);
	free(bmp);
	close(fd);
	exit_game(65307, arg);
}
