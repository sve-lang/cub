/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:45:22 by jrosemar          #+#    #+#             */
/*   Updated: 2020/10/27 14:45:23 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_get_resolution(char *line, t_info *arg, int n) // 24 lines
{
	line ++;
	while (*line != '\n' && *line != '\0')
	{
		if (ft_isdigit(*line) > 0)
		{
			if (n == 2)
			{
				n++;
				break;
			}
			if ((arg->res[n] = ft_atoi(line)) < 0)
			{
				ft_putstr("Error. Negative value of resolution\n");
				arg->error = 1;
			}
			line = line + findlen(arg->res[n]) - 1;
			n++;
		}
		
		
		line++;
	}
	if (n != 2 )
	{
		ft_putstr("Error. Too many values of resolution\n");
		arg->error = 1;
		return ;
	}
	if (arg->res[0] > 1920) 
		arg->res[0] = 1920;
	if (arg->res[1] > 1080)
		arg->res[1] = 1080;
}

char  *ft_get_path(char *line, t_info *arg) // 11 lines
{
	char *str;
	int len;

	line = line + 2;
	while (*line == ' ')
		line++;
	len = ft_strlen(line);
	if(!(str = (char *)malloc(sizeof(char)*len+1)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0000);
	ft_memcpy(str, line, len+1);
	return (str);
}

void ft_get_floor(char *line, t_info *arg) //25 lines
{
	int n;

	n = 0;
	line++;
	while (*line != '\n' && *line != '\0')
	{
		if (ft_isdigit(*line) > 0)
		{	
			arg->floor[n]=ft_atoi(line);
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
		if (n != 3 )
		{
			ft_putstr("Error. too many arguments of floor's color\n");
			arg->error = 1;
			return;
		}
}

void ft_get_celling(char *line, t_info *arg) //25 lines
{
	int n;

	n = 0;
	line++;
	while (*line != '\n' && *line != '\0')
	{
		if (ft_isdigit(*line) > 0)
		{						
			arg->cel[n]=ft_atoi(line);
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
	if (n != 3 )
	{
		ft_putstr("Error. too many arguments of celling's color\n");
		arg->error = 1;
		return ;
	}
}
int ft_check_arg(char c) // 6 lines
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W')
		return (1);
	if (c == 'E' || c == 'F' || c == 'C')
		return (1);
	else
		return (0);
}

void ft_parse_file2(t_info *arg, char *line) // 19 lines
{
	if (*line == 'R' && arg->res[0] == 0)
		ft_get_resolution (line, arg, 0);
	else if (*line == 'N' && *(line+1) == 'O' && arg->north == NULL)
		arg->north = ft_get_path(line, arg);			
	else if (*line == 'S' && *(line+1) == 'O' && arg->south == NULL)
		arg->south = ft_get_path(line, arg);
	else if (*line == 'W' && *(line+1) == 'E' && arg->west == NULL)
		arg->west = ft_get_path(line, arg);
	else if (*line == 'E' && *(line+1) == 'A' && arg->east == NULL)
		arg->east = ft_get_path(line, arg);
	else if (*line == 'S' && *(line+1) == ' ' && arg->sprite == NULL)
		arg->sprite= ft_get_path(line, arg);
	else if (*line == 'F' && *(line + 1) == ' ')
		ft_get_floor(line, arg);
	else if (*line == 'C' && *(line + 1) == ' ')
		ft_get_celling(line, arg);
}
void ft_destribute_text(t_info *arg) //18 lines
{
	if (arg->north == NULL || arg->south == NULL || arg->west == NULL || arg->east == NULL)
		ft_error("Error. one of the texture is missing\n", arg, 0);
	if ((arg->text.north_tex = ft_parse_texture(arg->north, arg)) == NULL)
		ft_error("Error reading noth texture\n", arg, 0);
	if ((arg->text.south_tex = ft_parse_texture(arg->south, arg)) == NULL)
		ft_error("Error reading south texture\n", arg, 0);
	if ((arg->text.west_tex = ft_parse_texture(arg->west, arg)) == NULL)
		ft_error("Error reading west texture\n", arg, 0);
	if ((arg->text.east_tex = ft_parse_texture(arg->east, arg)) == NULL)
		ft_error("Error reading east texture\n", arg,0);
	if (arg->sprite != NULL)
	{
		if((arg->text.sprite = ft_parse_sprite(arg->sprite, arg)) == NULL)
			ft_error("Error reading sprite\n", arg, 0);
	}
}
void ft_parse_file(t_info *arg, int fd) //21 lines
{
	char *line;
	int ret;
	int n;
	
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
	ft_check_map(arg->map, arg, 0, 0, 0);
	ft_destribute_text(arg);
}
