/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:31:26 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 16:31:29 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_text	init_text(void)
{
	t_text tex;

	tex.north_tex = NULL;
	tex.south_tex = NULL;
	tex.west_tex = NULL;
	tex.east_tex = NULL;
	tex.sprite = NULL;
	tex.spr_width = 0;
	tex.spr_height = 0;
	return (tex);
}

t_info		ft_init_info(int flag)
{
	t_info	arg;

	arg.res[0] = 0;
	arg.res[1] = 0;
	arg.north = NULL;
	arg.south = NULL;
	arg.west = NULL;
	arg.east = NULL;
	arg.sprite = NULL;
	arg.floor[0] = 0;
	arg.floor[1] = 0;
	arg.floor[2] = 0;
	arg.cel[0] = 0;
	arg.cel[1] = 0;
	arg.cel[2] = 0;
	arg.error = 0;
	arg.map = NULL;
	arg.mp = 0;
	arg.text = init_text();
	arg.spr = NULL;
	arg.flag = flag;
	return (arg);
}
