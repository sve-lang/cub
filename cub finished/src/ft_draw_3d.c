/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:32:12 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 21:49:03 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_draw_wall(t_info *arg, t_paint pt, int scale, int i)
{
	if (arg->cross[i] == 's')
		ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1,
		arg->text.south_tex[(int)(scale)][arg->coor_x[i] & (SIZE - 1)]);
	if (arg->cross[i] == 'n')
		ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1,
		arg->text.north_tex[(int)(scale)][arg->coor_x[i] & (SIZE - 1)]);
	if (arg->cross[i] == 'e')
		ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1,
		arg->text.east_tex[(int)(scale)][arg->coor_y[i] & (SIZE - 1)]);
	if (arg->cross[i] == 'w')
		ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1,
		arg->text.west_tex[(int)(scale)][arg->coor_y[i] & (SIZE - 1)]);
}

void		ft_init_paint(t_paint *pt, t_info *arg)
{
	pt->cell = (0 << 24 | arg->cel[0] << 16 | arg->cel[1] << 8 | arg->cel[2]);
	pt->floor = (0 << 24 | arg->floor[0] << 16 | arg->floor[1] << 8 |
	arg->floor[2]);
	pt->i = 0;
	pt->x1 = 0.0;
}

void		ft_init_paint2(t_paint *pt, t_info *arg)
{
	pt->d = 0;
	pt->distanse = arg->arr[pt->i] * cos(arg->corner[pt->i]);
	pt->h = SIZE / pt->distanse * (arg->res[0] / 2) / (M_PI / 3);
	pt->k = pt->h;
	pt->sc = pt->h / SIZE;
	if (pt->k > arg->res[1])
	{
		pt->d = (pt->k - arg->res[1]) / 2;
		pt->k = arg->res[1] - 1;
	}
	pt->y1 = ((arg->res[1]) / 2) - (pt->k / 2);
	pt->y = 0.0;
}

int			ft_draw_3d(t_info *arg)
{
	t_paint	pt;

	ft_init_paint(&pt, arg);
	while (pt.x1++ < arg->res[0])
	{
		ft_init_paint2(&pt, arg);
		while (pt.y++ <= pt.y1)
			ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y, pt.cell);
		while (pt.k--)
		{
			ft_draw_wall(arg, pt, (int)((pt.k + pt.d) / pt.sc), pt.i);
			pt.y1++;
		}
		while (pt.y1++ < arg->res[1])
			ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1, pt.floor);
		pt.i++;
	}
	ft_draw_sprite(arg);
	if (arg->flag != 0)
	{
		ft_create_bmp(arg);
		return (1);
	}
	mlx_put_image_to_window(arg->cub.mlx, arg->cub.win, arg->cub.img, 0, 0);
	return (0);
}
