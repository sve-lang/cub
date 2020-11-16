/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:26:33 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 21:16:08 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			ft_sort_sprite(t_info *arg, int i)
{
	t_sprite	*lst;
	t_sprite	*sprite_max;
	double		dist_max;

	dist_max = 0;
	while (dist_max != -1)
	{
		lst = arg->spr;
		dist_max = -1;
		while (lst != NULL)
		{
			if (lst->dist > dist_max)
			{
				dist_max = lst->dist;
				sprite_max = lst;
			}
			lst = lst->next;
		}
		if (dist_max != -1)
		{
			ft_draw_sprite2(arg, sprite_max, -1, -1);
			sprite_max->dist = -1;
		}
		i++;
	}
}

int				get_color(t_info *arg, double h, double w)
{
	return (arg->text.sprite[(int)((float)(arg->text.spr_height * h))]
	[(int)((float)(arg->text.spr_width * w))]);
}

void			ft_draw_sprite2(t_info *arg, t_sprite *spr, int i, int j)
{
	int			x;
	int			y;
	double		w;
	double		h;
	int			color;

	w = (double)arg->text.spr_width / spr->dist * arg->res[1];
	h = (double)arg->text.spr_height / spr->dist * arg->res[1];
	x = (spr->corner - (M_PI / 6)) * (arg->res[0] / (M_PI / 3)) +
	arg->res[0] - w / 2;
	y = arg->res[1] / 2 - h / 2;
	while (++j <= w && (j + x) < arg->res[0])
	{
		if ((x + j) >= 0 && (x + j) < arg->res[0] && arg->arr[x + j] >
		spr->dist)
		{
			i = -1;
			while (++i <= h)
			{
				color = get_color(arg, (double)(i / h), (double)(j / w));
				if (color != 0)
					ft_mlx_pixel_put(&arg->cub, x + j, y + i, color);
			}
		}
	}
}

void			ft_draw_sprite(t_info *arg)
{
	t_sprite	*lst;

	lst = arg->spr;
	while (lst != NULL)
	{
		lst->corner = atan2(arg->player.y - lst->y, lst->x - arg->player.x);
		if (lst->corner < 0 && arg->player.corner >= (M_PI / 6) &&
		arg->player.corner <= (M_PI * 2 - M_PI / 6))
			lst->corner += 2 * M_PI;
		if (arg->player.corner >= (M_PI * 2 - M_PI / 6))
			lst->corner += 2 * M_PI;
		lst->corner = arg->player.corner - lst->corner;
		if (lst->corner > -M_PI / 4 && lst->corner < M_PI / 4)
			lst->dist = sqrt(pow(arg->player.x - lst->x, 2) +
			pow(arg->player.y - lst->y, 2));
		else
			lst->dist = -1;
		if (lst->dist > 0 && lst->dist < SIZE)
			lst->dist = -1;
		lst = lst->next;
	}
	ft_sort_sprite(arg, 0);
}
