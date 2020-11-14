/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:32:12 by jrosemar          #+#    #+#             */
/*   Updated: 2020/10/27 15:32:15 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char    *dst;
	
    dst = data->addr + (y * data->length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void ft_init_player(t_player *player, char c, double x, double y) //10 lines
{
	if (c == 'N')
		player->corner =  M_PI/2;
	if (c == 'W')
		player->corner = M_PI;
	if (c == 'E')
		player->corner = 0.00;
	if (c == 'S')
		player->corner =  3 *M_PI/2;
	player->x = x + SIZE/2;
	player->y = y + SIZE/2;
}

t_player ft_find_player(t_info *arg)// определяет координаты игрока 24 lines
{
	int n;
	int m;
	int x;
	int y;
	x = 0;
	y = 0;
	t_player player;

	m = 0;
	while (m < arg->mp)
	{
		n = 0;
		x = 0;
		while (arg->map[m][n] != '\0')
		{
			if (arg->map[m][n] == 'N' || arg->map[m][n] == 'W' || arg->map[m][n] == 'E' || arg->map[m][n]=='S')
				ft_init_player(&player, arg->map[m][n], (double)x, (double)y);			
			n++;
			x = x + SIZE;
		}
		y = y + SIZE;
		m++;
	}
	return (player);
}
void ft_fill_bmp(char *bmp, int num, int size, t_info *arg) //14 lines
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
void ft_create_bmp(t_info *arg) // 14 lines
{
	int size;
	char *bmp;
	int fd;

	size = (arg->res[0]* arg->res[1] * 4) + 54;
	if(!(bmp = (char *)malloc(size)))
		ft_error("Error! Failed to allocate memory.\n", arg, 65307);
	ft_fill_bmp(bmp, 54, size, arg);
	fd = open("cub.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, bmp, size);
	free(bmp);
	close(fd);
	exit_game(65307, arg);
	
}
void ft_draw_wall(t_info *arg, double x1, double y1, int scale, int i)
{
	if (arg->cross[i] == 's')
		ft_mlx_pixel_put(&arg->cub, x1, y1, arg->text.south_tex[(int)(scale)][arg->coor_x[i] & (SIZE-1)]);
	if (arg->cross[i] == 'n')
		ft_mlx_pixel_put(&arg->cub, x1, y1, arg->text.north_tex[(int)(scale)][arg->coor_x[i] & (SIZE-1)]);
	if (arg->cross[i] == 'e')
		ft_mlx_pixel_put(&arg->cub, x1, y1, arg->text.east_tex[(int)(scale)][arg->coor_y[i] & (SIZE-1)]);		
	if (arg->cross[i] == 'w')
		ft_mlx_pixel_put(&arg->cub, x1, y1, arg->text.west_tex[(int)(scale)][arg->coor_y[i] & (SIZE-1)]);
}

void ft_init_paint(t_paint *pt, t_info *arg)
{
	pt->cell =  (0<<24| arg->cel[0]<<16 | arg->cel[1]<<8 | arg->cel[2]);
	pt->floor = (0<<24| arg->floor[0]<<16 | arg->floor[1]<<8 | arg->floor[2]);
	pt->i = 0;
	pt->x1 = 0.0;
}
void ft_init_paint2(t_paint *pt, t_info *arg)
{
	pt->distanse = arg->arr[pt->i] * cos(arg->corner[pt->i]); 
	pt->h = SIZE / pt->distanse * (arg->res[0]/2)/(M_PI/3);
	pt->k = pt->h;
	pt->scale = pt->h/SIZE;
	if (pt->k > arg->res[1])
		pt->k = arg->res[1] - 1;
	pt->y1 = ((arg->res[1])/2)-(pt->k/2);
	pt->y = 0.0;
}
int ft_draw_3d(t_info *arg) // отрисовка 3д карты 26 lines
{
	t_paint pt;
	
	ft_init_paint(&pt, arg);	
	while (pt.x1++ < arg->res[0])
	{
		ft_init_paint2(&pt, arg);
		while (pt.y++ <= pt.y1)
			ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y, pt.cell);
		while (pt.k--)
		{				
			ft_draw_wall(arg, pt.x1, pt.y1,(int)(pt.k/pt.scale), pt.i);
			pt.y1++;
		}
		while (pt.y1++ <= arg->res[1])
			ft_mlx_pixel_put(&arg->cub, pt.x1, pt.y1, pt.floor);
		pt.i++;
	}
	
	ft_draw_sprite(arg);
	if (arg->flag != 0 )
	{	
		ft_create_bmp(arg);
		return (1);
	}
	mlx_put_image_to_window(arg->cub.mlx, arg->cub.win, arg->cub.img, 0, 0);
	return(0);
} 

