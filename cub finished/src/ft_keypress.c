/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:13:36 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 18:54:34 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_moveupdown(t_info *arg, int key)
{
	double	x;
	double	y;

	x = arg->player.x;
	y = arg->player.y;
	if (key == W || key == UP)
	{
		y -= SIZE / 3 * sin(arg->player.corner);
		x += SIZE / 3 * cos(arg->player.corner);
	}
	if (key == S || key == DOWN)
	{
		y += SIZE / 3 * sin(arg->player.corner);
		x -= SIZE / 3 * cos(arg->player.corner);
	}
	if (arg->map[(int)(y / SIZE)][(int)(arg->player.x / SIZE)] != '1')
		arg->player.y = y;
	if (arg->map[(int)(arg->player.y / SIZE)][(int)(x / SIZE)] != '1')
		arg->player.x = x;
}

void		ft_moverightleft(t_info *arg, int key)
{
	double	corner;

	corner = arg->player.corner;
	if (key == A)
	{
		corner -= M_PI / 2;
		arg->player.y -= SIZE / 3 * sin(corner);
		arg->player.x += SIZE / 3 * cos(corner);
	}
	if (key == D)
	{
		corner += M_PI / 2;
		arg->player.y -= SIZE / 3 * sin(corner);
		arg->player.x += SIZE / 3 * cos(corner);
	}
}

int			ft_keypress(int key, t_info *arg)
{
	mlx_clear_window(arg->cub.mlx, arg->cub.win);
	while (arg->player.corner > 2 * M_PI)
		arg->player.corner -= 2 * M_PI;
	while (arg->player.corner < 0.0)
		arg->player.corner += 2 * M_PI;
	if (key == W || key == UP || key == S || key == DOWN)
		ft_moveupdown(arg, key);
	if (key == A || key == D)
		ft_moverightleft(arg, key);
	if (key == LEFT)
		arg->player.corner -= 64 * ((M_PI / 3) / arg->res[0]);
	if (key == RIGHT)
		arg->player.corner += 64 * ((M_PI / 3) / arg->res[0]);
	if (key == 65307)
		exit_game(key, arg);
	ft_put_ray(arg);
	mlx_put_image_to_window(arg->cub.mlx, arg->cub.win, arg->cub.img, 0, 0);
	return (1);
}
