/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:27:17 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 16:48:02 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int			ft_check_main_arguments(int argc, char **argv)
{
	char	*name_map;

	if (argc < 2 || argc > 3)
	{
		ft_putstr("ERROR! incorrect number of arguments\n");
		return (-1);
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
		{
			ft_putstr("Error. Wrong the second argument\n");
			return (-1);
		}
		return (3);
	}
	name_map = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strncmp(name_map, ".cub", 5) != 0)
	{
		free(name_map);
		ft_putstr("Error. the wrong file extension\n");
		return (-1);
	}
	free(name_map);
	return (1);
}

int			ft_read_file(char *filename, t_info *arg, int flag)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error!");
		return (-1);
	}
	ft_parse_file(arg, fd);
	if (arg->error == 1)
		return (-1);
	close(fd);
	return (0);
}

void		ft_error(char *str, t_info *arg, int mistake)
{
	ft_putstr(str);
	exit_game(mistake, arg);
}

int			main(int argc, char **argv)
{
	t_info	arg;
	int		flag;

	flag = 0;
	if (ft_check_main_arguments(argc, argv) == -1)
		return (0);
	flag = (ft_check_main_arguments(argc, argv) == 3) ? 1 : 0;
	arg = ft_init_info(flag);
	if (ft_read_file(argv[1], &arg, flag) == -1)
		exit_game(0, NULL);
	arg.cub.mlx = mlx_init();
	if (flag != 1)
		arg.cub.win = mlx_new_window(arg.cub.mlx, arg.res[0],
		arg.res[1], "CUB3D");
	arg.cub.img = mlx_new_image(arg.cub.mlx, arg.res[0], arg.res[1]);
	arg.cub.addr = mlx_get_data_addr(arg.cub.img, &arg.cub.bits_per_pixel,
	&arg.cub.length, &arg.cub.endian);
	arg.player = ft_find_player(&arg);
	ft_find_sprites(&arg);
	if ((ft_put_ray(&arg)) == 1)
		return (0);
	mlx_hook(arg.cub.win, 2, (1L << 0), ft_keypress, &arg);
	mlx_hook(arg.cub.win, 17, 1L << 17, exit_game, &arg);
	mlx_loop(arg.cub.mlx);
	return (0);
}
