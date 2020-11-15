/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:58:52 by jrosemar          #+#    #+#             */
/*   Updated: 2020/10/27 14:58:55 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_check_sym(char *str, char c) //7 lines
{
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void ft_check_map4(char **map, t_info *arg, int i, int j) // 10 lines
{
	if ((map[j][i + 1] == ' ') || (map[j][i - 1] == ' ') || (map[j + 1][i] == ' ') || (map[j - 1][i] == ' '))
		ft_error("Error. Map is not closed\n", arg, 0000);
	if ((map[j- 1][i - 1] == ' ') || (map[j-1][i + 1] == ' ') || (map[j + 1][i - 1] == ' ') || (map[j + 1][i+1] == ' '))
		ft_error("Error. Map is not closed\n", arg, 0000);
}

void ft_check_map3(char **map, t_info *arg, int max) // ловится сега при неполном угле 24 lines

{
	int i;
	int j;

	j = 0;
	while (j < arg->mp)
	{
		i = 0;
		while (i < max)
		{
			if (j == 0 || j == (arg->mp - 1))
			{
				if(ft_strrchr(" 1", map[j][i]) == NULL)
					ft_error("Error. Map is not closed\n", arg, 0000);
			}
			if (map[j][i] == '0')
				ft_check_map4(map, arg, i, j);
			i++;
		}
		j++;
	}
}
void ft_check_map2(char **map, t_info *arg, int max, int i, int j) // 24 lines
{
	int player;

	player = 0;
	while (j < arg->mp)
	{
		i = 0;
		while (i < max)
		{
			if(ft_strrchr(" 012WESN", map[j][i]) == NULL)
				ft_error("Error. Wrong value of argument in the map\n", arg, 0000);
			if (ft_strrchr("WESN", map[j][i]) != NULL)
				player++;
			i++;
		}
		j++;
	}
	if (player > 1 || player < 1)
		ft_error("Error. Wrong number of player in the map\n", arg, 0000);
	ft_check_map3(map, arg, max);
}
void ft_check_map (char **map, t_info *arg, int x, int y, int max) // нет проверки на невалидные символы 28 lines
{
	char **arr_max;
	while (y < arg->mp)
	{
		x = 0;
		while(map[y][x] != '\0')
			x++;
		if (x > max)
			max = x;
		y++;
	}
	arg->pm = max;
	if (!(arr_max = (char **)malloc(sizeof(char*) * arg->mp)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0000);
	x = 0;
	while(x < arg->mp)
	{
		if (!(arr_max[x] = (char *)malloc(sizeof(char) * max + 1)))
			ft_error("Error! Failed to allocate memory.\n", arg, 0000);
		ft_memset(arr_max[x], ' ', max);
		ft_memcpy(arr_max[x], map[x], ft_strlen(map[x]));
		arr_max[x][max] = '\0';
		x++;
	}
	free_map(arg->map, arg->mp);
	arg->map = arr_max;
	ft_check_map2(arr_max, arg, max, 0, 0);
}
