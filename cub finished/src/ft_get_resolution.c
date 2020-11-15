/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:29:19 by jrosemar          #+#    #+#             */
/*   Updated: 2020/11/15 19:25:00 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int			check(char c)
{
	if (c == ' ' || c == '\t' || c == ',' || c == '\n' || c == '\0')
		return (0);
	if (ft_isdigit(c) > 0)
		return (0);
	return (1);
}

void		ft_get_resol(t_info *arg, int n, char line)
{
	if (n != 2 || check(line) == 1)
	{
		ft_putstr("Error. Wrong values or count resolution\n");
		arg->error = 1;
		return ;
	}
	if (arg->res[0] > 1920)
		arg->res[0] = 1920;
	if (arg->res[1] > 1080)
		arg->res[1] = 1080;
	if (arg->res[0] == 0 && arg->res[1] == 0)
	{
		arg->res[0] = 1920;
		arg->res[1] = 1080;
	}
}

void		ft_get_resolution(char *line, t_info *arg, int n)
{
	line++;
	while (*line != '\n' && *line != '\0' && check(*line) == 0)
	{
		if (ft_isdigit(*line) > 0)
		{
			if (n == 2)
			{
				n++;
				break ;
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
	ft_get_resol(arg, n, *line);
}

char		*ft_get_path(char *line, t_info *arg)
{
	char	*str;
	int		len;

	line = line + 2;
	while (*line == ' ')
		line++;
	len = ft_strlen(line);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0000);
	ft_memcpy(str, line, len + 1);
	return (str);
}

int			ft_check_arg(char c)
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W')
		return (1);
	if (c == 'E' || c == 'F' || c == 'C')
		return (1);
	else
		return (0);
}
