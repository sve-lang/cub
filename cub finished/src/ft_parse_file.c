/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:45:22 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 18:48:43 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_get_floor(char *line, t_info *arg)
{
	int		n;

	n = 0;
	line++;
	while (*line != '\n' && *line != '\0' && (check(*line) == 0))
	{
		if (ft_isdigit(*line) > 0)
		{
			arg->floor[n] = ft_atoi(line);
			if (arg->floor[n] < 0 || arg->floor[n] > 255)
			{
				ft_putstr("Error. wrong value of floor's color\n");
				arg->error = 1;
			}
			line = line + findlen(arg->floor[n]) - 1;
			n++;
		}
		line++;
	}
	if (n != 3 || check(*line) == 1)
	{
		ft_putstr("Error. too many arguments of floor's color\n");
		arg->error = 1;
		return ;
	}
}

void		ft_get_celling(char *line, t_info *arg)
{
	int		n;

	n = 0;
	line++;
	while (*line != '\n' && *line != '\0' && (check(*line) == 0))
	{
		if (ft_isdigit(*line) > 0)
		{
			arg->cel[n] = ft_atoi(line);
			if (arg->cel[n] < 0 || arg->cel[n] > 255)
			{
				ft_putstr("Error. Wrong value of celling's color\n");
				arg->error = 1;
			}
			line = line + findlen(arg->cel[n]) - 1;
			n++;
		}
		line++;
	}
	if (n != 3 || check(*line) == 1)
	{
		ft_putstr("Error. too many arguments of celling's color\n");
		arg->error = 1;
		return ;
	}
}

void		ft_parse_file2(t_info *arg, char *line)
{
	if (*line == 'R' && arg->res[0] == 0)
		ft_get_resolution(line, arg, 0);
	else if (*line == 'N' && *(line + 1) == 'O' && arg->north == NULL)
		arg->north = ft_get_path(line, arg);
	else if (*line == 'S' && *(line + 1) == 'O' && arg->south == NULL)
		arg->south = ft_get_path(line, arg);
	else if (*line == 'W' && *(line + 1) == 'E' && arg->west == NULL)
		arg->west = ft_get_path(line, arg);
	else if (*line == 'E' && *(line + 1) == 'A' && arg->east == NULL)
		arg->east = ft_get_path(line, arg);
	else if (*line == 'S' && *(line + 1) == ' ' && arg->sprite == NULL)
		arg->sprite = ft_get_path(line, arg);
	else if (*line == 'F' && *(line + 1) == ' ')
		ft_get_floor(line, arg);
	else if (*line == 'C' && *(line + 1) == ' ')
		ft_get_celling(line, arg);
}

void		ft_destribute_text(t_info *arg)
{
	if (arg->north == NULL || arg->south == NULL)
		ft_error("Error. one of the texture is missing\n", arg, 0);
	if (arg->west == NULL || arg->east == NULL)
		ft_error("Error. one of the texture is missing\n", arg, 0);
	if ((arg->text.north_tex = ft_parse_texture(arg->north, arg)) == NULL)
		ft_error("Error reading noth texture\n", arg, 0);
	if ((arg->text.south_tex = ft_parse_texture(arg->south, arg)) == NULL)
		ft_error("Error reading south texture\n", arg, 0);
	if ((arg->text.west_tex = ft_parse_texture(arg->west, arg)) == NULL)
		ft_error("Error reading west texture\n", arg, 0);
	if ((arg->text.east_tex = ft_parse_texture(arg->east, arg)) == NULL)
		ft_error("Error reading east texture\n", arg, 0);
	if (arg->sprite != NULL)
	{
		if ((arg->text.sprite = ft_parse_sprite(arg->sprite, arg)) == NULL)
			ft_error("Error reading sprite\n", arg, 0);
	}
}

void		ft_parse_file(t_info *arg, int fd)
{
	char	*line;
	int		ret;
	int		n;

	n = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if ((ft_check_arg(*line)) == 1)
			ft_parse_file2(arg, line);
		else if (ft_check_sym(line, '1') == 1)
		{
			ft_parse_map(line, n, arg);
			n++;
		}
		free(line);
	}
	arg->mp = n;
	ft_check_map(arg, 0, -1, 0);
	ft_destribute_text(arg);
}
