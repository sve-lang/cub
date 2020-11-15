/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:03:42 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 19:33:19 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				**ft_parse_sprite(char *path, t_info *arg)
{
	int			**arr_text;
	int			*arr_addr;
	t_mlx		img;

	img.mlx = mlx_init();
	if (!(img.img = mlx_xpm_file_to_image(img.mlx, path, &img.width,
	&img.height)))
		ft_error("Error. wrong path to sprite\n", arg, 0);
	arg->text.spr_height = img.height;
	arg->text.spr_width = img.width;
	arr_addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
	&img.length, &img.endian);
	arr_text = ft_add_memory(&img, arr_addr, 0, arg);
	mlx_destroy_image(img.mlx, img.img);
	free(img.mlx);
	return (arr_text);
}

t_sprite		**ft_unite_sprite(t_sprite *sprt, int n, t_info *arg)
{
	t_sprite	**list;
	int			i;

	i = 0;
	if (!(list = (t_sprite **)malloc(sizeof(t_sprite *) * (n + 1))))
		ft_error("Error! Failed to allocate memory.\n", arg, 65307);
	while (i < n)
	{
		list[i] = sprt;
		sprt = sprt->next;
		i++;
	}
	list[i] = NULL;
	return (list);
}

void			ft_create_sprite(int x, int y, t_info *arg)
{
	t_sprite	*lst;
	t_sprite	*new;

	if (!(new = (t_sprite *)malloc(sizeof(t_sprite))))
		ft_error("Error! Failed to allocate memory.\n", arg, 65307);
	if (arg->spr == NULL)
		arg->spr = new;
	else
	{
		lst = arg->spr;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
	new->x = x * SIZE + SIZE / 2;
	new->y = y * SIZE + SIZE / 2;
	new->next = NULL;
}

void			ft_find_sprites(t_info *arg)
{
	int			x;
	int			y;
	int			count;

	y = 0;
	count = 0;
	while (y < arg->mp)
	{
		x = 0;
		while (x < arg->pm)
		{
			if (arg->map[y][x] == '2')
			{
				ft_create_sprite(x, y, arg);
				count++;
			}
			x++;
		}
		y++;
	}
}
