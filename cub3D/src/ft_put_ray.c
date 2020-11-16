/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:10:12 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 17:44:05 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				ft_cross_map(t_info *arg, double x, double y)
{
	x = (int)x / SIZE;
	y = (int)y / SIZE;
	if ((int)x > arg->pm - 1 || (int)y > arg->mp - 1 || x < 0 || y < 0)
		return (-1);
	if (arg->map[(int)y][(int)x] == ' ')
		return (-1);
	if (arg->map[(int)y][(int)x] == '1')
		return (1);
	else
		return (0);
}

double			ft_find_dist(t_info *arg, t_cross cr, t_cross *rs)
{
	while (ft_cross_map(arg, cr.x, cr.y) == 0)
	{
		cr.x += cr.delta_x;
		cr.y += cr.delta_y;
	}
	rs->x = cr.x;
	rs->y = cr.y;
	if (ft_cross_map(arg, cr.x, cr.y) == 0)
		return (99999999);
	return (sqrt(pow(arg->player.x - cr.x, 2) + pow(arg->player.y - cr.y, 2)));
}

double			ft_cross_x(t_info *arg, double corner, t_cross *rs, int n)
{
	t_cross		cr;

	cr.delta_y = SIZE;
	cr.delta_x = SIZE / tan(corner);
	if ((corner > 0 && corner < M_PI) || corner > M_PI * 2)
	{
		cr.y = (int)(arg->player.y / SIZE) * SIZE - 0.005;
		cr.delta_y = -cr.delta_y;
		arg->cross[n] = 'n';
	}
	else
	{
		cr.y = (int)(arg->player.y / SIZE) * SIZE + SIZE;
		cr.delta_x = -cr.delta_x;
		arg->cross[n] = 's';
	}
	cr.x = arg->player.x + (arg->player.y - cr.y) / tan(corner);
	return (ft_find_dist(arg, cr, rs));
}

double			ft_cross_y(t_info *arg, double corner, t_cross *rs, int n)
{
	t_cross		cr;

	cr.delta_x = SIZE;
	cr.delta_y = SIZE * tan(corner);
	if (corner > M_PI / 2 && corner < M_PI * 3 / 2)
	{
		cr.x = (int)(arg->player.x / SIZE) * SIZE - 0.005;
		cr.delta_x = -cr.delta_x;
		arg->cross[n] = 'w';
	}
	else
	{
		cr.x = (int)(arg->player.x / SIZE) * SIZE + SIZE;
		cr.delta_y = -cr.delta_y;
		arg->cross[n] = 'e';
	}
	cr.y = arg->player.y + (arg->player.x - cr.x) * tan(corner);
	return (ft_find_dist(arg, cr, rs));
}

int				ft_put_ray(t_info *arg)
{
	t_cross		rs;
	double		st;
	double		end;
	int			n;

	n = 0;
	rs.x = 0;
	rs.y = 0;
	st = arg->player.corner + M_PI / 6;
	end = arg->player.corner - M_PI / 6;
	while (st > end && n < arg->res[0])
	{
		if (ft_cross_x(arg, st, &rs, n) < ft_cross_y(arg, st, &rs, n))
			arg->arr[n] = ft_cross_x(arg, st, &rs, n);
		else
			arg->arr[n] = ft_cross_y(arg, st, &rs, n);
		arg->coor_x[n] = rs.x;
		arg->coor_y[n] = rs.y;
		arg->cor_pl[n] = st;
		arg->corner[n] = st - arg->player.corner;
		st = st - ((M_PI / 3) / arg->res[0]);
		n++;
	}
	return (ft_draw_3d(arg));
}
