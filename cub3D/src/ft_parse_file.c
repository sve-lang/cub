/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:45:22 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/16 14:50:46 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	else
	{
		ft_putstr("Error! An unexpected error occurred\n");
		arg->error = 1;
	}
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

int			check_parsed(t_info *arg)
{
	int		i;

	i = 0;
	if (arg->res[0] != 0 && arg->res[1] != 0)
		i++;
	if (arg->floor[0] != -1 || arg->floor[1] != -1 || arg->floor[2] != -1)
		i++;
	if (arg->cel[0] != -1 || arg->cel[1] != -1 || arg->cel[2] != -1)
		i++;
	if (arg->sprite != NULL)
		i++;
	if (arg->north != NULL)
		i++;
	if (arg->south != NULL)
		i++;
	if (arg->west != NULL)
		i++;
	if (arg->east != NULL)
		i++;
	if (i == 8)
		return (1);
	return (0);
}

void		ft_parse_file(t_info *arg, int fd)
{
	char	*line;
	int		ret;

	ret = 1;
	while ((ret = get_next_line(fd, &line)) != 0)
	{
		if ((ft_check_arg(*line)) == 1)
			ft_parse_file2(arg, line);
		else if ((*line == '\0' || *line == '\n') && arg->map == NULL)
		{
			free(line);
			continue;
		}
		else if ((ft_check_sym(line, '1') == 1 && check_parsed(arg) == 1) ||
		(*line == '\0' || *line == '\n'))
		{
			ft_parse_map(line, arg->mp, arg);
			arg->mp++;
		}
		else
			break ;
		free(line);
	}
	ft_check_map(arg, 0, -1, 0);
	ft_destribute_text(arg);
}
