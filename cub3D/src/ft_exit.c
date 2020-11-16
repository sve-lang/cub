/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:06:47 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 19:50:11 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		free_double_array(int **arr, int height)
{
	int	j;

	j = 0;
	while (j < height)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

void		free_map(char **arr, int h)
{
	int		j;

	j = 0;
	while (j < h)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

void		free_sprite(t_info *arg)
{
	t_sprite	*ptr;

	while (arg->spr->next != NULL)
	{
		ptr = arg->spr;
		arg->spr = arg->spr->next;
		free(ptr);
	}
}

int			clean_memory(t_info *arg)
{
	if (arg->north != NULL)
		free(arg->north);
	if (arg->south != NULL)
		free(arg->south);
	if (arg->west != NULL)
		free(arg->west);
	if (arg->east != NULL)
		free(arg->east);
	if (arg->text.east_tex != NULL)
		free_double_array(arg->text.east_tex, SIZE);
	if (arg->text.west_tex != NULL)
		free_double_array(arg->text.west_tex, SIZE);
	if (arg->text.north_tex != NULL)
		free_double_array(arg->text.north_tex, SIZE);
	if (arg->text.south_tex != NULL)
		free_double_array(arg->text.south_tex, SIZE);
	if (arg->text.sprite != NULL)
		free_double_array(arg->text.sprite, arg->text.spr_height);
	if (arg->map != NULL)
		free_map(arg->map, arg->mp);
	if (arg->spr != NULL)
		free_sprite(arg);
	return (0);
}

int			exit_game(int key, t_info *arg)
{
	if (key != 0000)
		ft_putstr("Game is over!\n");
	if (key == 65307)
	{
		mlx_destroy_image(arg->cub.mlx, arg->cub.img);
		if (arg->cub.win)
			mlx_destroy_window(arg->cub.mlx, arg->cub.win);
	}
	if (arg != NULL && (key == 0 || key == 65307))
	{
		clean_memory(arg);
	}
	exit(0);
	return (0);
}
