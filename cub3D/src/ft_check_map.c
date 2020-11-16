/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:58:52 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 22:19:28 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int			ft_check_sym(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void		ft_check_map4(char **map, t_info *arg, int i, int j)
{
	if ((map[j][i + 1] == ' ') || (map[j][i - 1] == ' ') ||
	(map[j + 1][i] == ' ') || (map[j - 1][i] == ' '))
		ft_error("Error. Map is not closed\n", arg, 0);
	if ((map[j - 1][i - 1] == ' ') || (map[j - 1][i + 1] == ' ') ||
	(map[j + 1][i - 1] == ' ') || (map[j + 1][i + 1] == ' '))
		ft_error("Error. Map is not closed\n", arg, 0);
	if ((map[j][i + 1] == '\n') || (map[j][i - 1] == '\n') ||
	(map[j + 1][i] == '\n') || (map[j - 1][i] == '\n'))
		ft_error("Error. Map is not closed\n", arg, 0);
	if ((map[j - 1][i - 1] == '\n') || (map[j - 1][i + 1] == '\n') ||
	(map[j + 1][i - 1] == '\n') || (map[j + 1][i + 1] == '\n'))
		ft_error("Error. Map is not closed\n", arg, 0);
	if ((map[j][i + 1] == '\0') || (map[j][i - 1] == '\0') ||
	(map[j + 1][i] == '\0') || (map[j - 1][i] == '\0'))
		ft_error("Error. Map is not closed\n", arg, 0);
	if ((map[j - 1][i - 1] == '\0') || (map[j - 1][i + 1] == '\0') ||
	(map[j + 1][i - 1] == '\0') || (map[j + 1][i + 1] == '\0'))
		ft_error("Error. Map is not closed\n", arg, 0);
}

void		ft_check_map3(char **map, t_info *arg, int max)
{
	int		i;
	int		j;

	j = 0;
	while (j < arg->mp)
	{
		i = 0;
		while (i < max)
		{
			if (j == 0 || j == (arg->mp - 1))
			{
				if (ft_strrchr(" 1", map[j][i]) == NULL)
					ft_error("Error. Map is not closed\n", arg, 0);
			}
			if (map[j][i] == '0' || map[j][i] == '2' || map[j][i] == 'N')
				ft_check_map4(map, arg, i, j);
			if (map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E')
				ft_check_map4(map, arg, i, j);
			i++;
		}
		j++;
	}
}

void		ft_check_map2(t_info *arg, int max, int i, int j)
{
	int		player;

	player = 0;
	while (j < arg->mp)
	{
		i = 0;
		while (i < max)
		{
			if (ft_strrchr(" 012WESN", arg->map[j][i]) == NULL)
				ft_error("Error. Wrong value of argument in the map\n", arg, 0);
			if (ft_strrchr("WESN", arg->map[j][i]) != NULL)
				player++;
			i++;
		}
		j++;
	}
	if (player > 1 || player < 1)
		ft_error("Error. Wrong number of player in the map\n", arg, 0);
	ft_check_map3(arg->map, arg, max);
}

void		ft_check_map(t_info *arg, int x, int y, int max)
{
	char	**arr_max;

	while (++y < arg->mp)
	{
		x = 0;
		while (arg->map[y][x] != '\0')
			x++;
		if (x > max)
			max = x;
	}
	arg->pm = max;
	if (!(arr_max = (char **)malloc(sizeof(char*) * arg->mp)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0);
	x = -1;
	while (++x < arg->mp)
	{
		if (!(arr_max[x] = (char *)malloc(sizeof(char) * max + 1)))
			ft_error("Error! Failed to allocate memory.\n", arg, 0);
		ft_memset(arr_max[x], ' ', max);
		ft_memcpy(arr_max[x], arg->map[x], ft_strlen(arg->map[x]));
		arr_max[x][max] = '\0';
	}
	free_map(arg->map, arg->mp);
	arg->map = arr_max;
	ft_check_map2(arg, max, 0, 0);
}
