/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:27:17 by jrosemar          #+#    #+#             */
/*   Updated: 2020/09/16 17:09:18 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


t_text init_text(void)
{
	t_text tex;

	tex.north_tex = NULL;
	tex.south_tex = NULL;
	tex.west_tex = NULL;
	tex.east_tex = NULL;
	tex.sprite = NULL;
	tex.spr_width = 0;
	tex.spr_height = 0;
	return(tex);

}
t_info ft_init_info(int flag) // 27 cтроки
{
	t_info arg;

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
	arg.text.north_tex = NULL;
	arg.text.south_tex = NULL;
	arg.text.west_tex = NULL;
	arg.text.east_tex = NULL;
	
	//arg.text = init_text();
	arg.spr = NULL;
	arg.flag = flag;
	
	return (arg);
	
}

int ft_check_main_arguments(int argc, char **argv) // 25 lines
{
	char *name_map;
	
	if (argc < 2 || argc > 3)
	{
		ft_putstr("ERROR! incorrect number of arguments\n");
		return (-1);
	}
	name_map = ft_substr(argv[1], ft_strlen(argv[1])- 4,  4);
	if (ft_strncmp(name_map, ".cub", 5) != 0) // рассмотреть вариант двойного расширения 
	{
		free(name_map);
		ft_putstr("Error. the wrong file extension\n");
		return(-1);
	}
	if (argc ==  3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
		{	
				free(name_map);
				ft_putstr("Error. Wrong the second argument\n");
				return(-1);
		}
		return(3);
	}
	free(name_map);
	return (1);
}
int ft_read_file(char *filename, t_info *arg, int flag) // 13 lines
{
	int fd;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error!");
		return (-1);
	}
	ft_parse_file(arg, fd);
	if (arg->error == 1)
		return(-1);
	close (fd);
	return(0);
}
void free_double_array (int **arr, int height)
{
	int j;
	j = 0;
	while (j < height)
	{
		free(arr[j]);
		j++;
	}
	printf("j = %d\n", j);
	free(arr);
}
void free_map(char **arr, int h)
{
	int j;
	j = 0;
	while (j < h)
	{
		free(arr[j]);
		j++;
	}
	//printf("j = %d\n", j);
	free(arr);
}
int clean_memory(t_info *arg)
{
	t_sprite *ptr;
	
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
	{
		while (arg->spr->next != NULL)
		{
			ptr = arg->spr;
			arg->spr = arg->spr->next;
			free(ptr);
		}
	}
	//free(arg->cub.mlx);
	
	return (0);

}
int exit_game(int key, t_info *arg)
{
	ft_putstr("Game is over!\n");
	if (key == 65307)
	{
		mlx_destroy_image(arg->cub.mlx, arg->cub.img);
		if(arg->cub.win)
			mlx_destroy_window(arg->cub.mlx, arg->cub.win);
		clean_memory(arg);
	}
	exit(0);
	return (0);
}

int main(int argc, char **argv) // 23 lines
{
	t_info arg;
	int flag;
	flag = 0;
	if (ft_check_main_arguments(argc, argv) == -1)
		return (0);
	if ((ft_check_main_arguments(argc, argv) == 3))
		flag = 1;
	arg = ft_init_info(flag);	
	if (ft_read_file(argv[1], &arg, flag) == -1)
		return (0);
	arg.cub.mlx = mlx_init();
	if (flag != 1)
		arg.cub.win = mlx_new_window(arg.cub.mlx, arg.res[0], arg.res[1], "CUB3D");
	arg.cub.img = mlx_new_image(arg.cub.mlx, arg.res[0], arg.res[1]);
	arg.cub.addr = mlx_get_data_addr(arg.cub.img, &arg.cub.bits_per_pixel, &arg.cub.length, &arg.cub.endian);
	arg.player = ft_find_player(&arg);
	ft_find_sprites(&arg);
	if ((ft_put_ray(&arg)) == 1)
		return(0);
	mlx_hook(arg.cub.win, 2, (1L << 0), ft_keypress, &arg);
	mlx_hook(arg.cub.win, 17, 1L << 17, exit_game, &arg);
	mlx_loop(arg.cub.mlx);
	if (arg.map != NULL)
		free_map(arg.map, arg.mp); 
	return (0);
}
