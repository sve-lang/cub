/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:30:23 by jrosemar          #+#    #+#             */
/*   Updated: 2020/10/27 15:30:31 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_parse_map(char *line, int n, t_info *arg)//возможна утечка 25 lines
{
	char **arr;
	int i;
	arr = arg->map;
	i = 0;
	if (!(arg->map = (char **)malloc(sizeof(char *)*(n+1))))
		ft_error("Error! Failed to allocate memory.\n", arg, 0000);
	while (i < n)
	{
		if (!(arg->map[i]= (char *)malloc(sizeof(char)* ft_strlen(arr[i])+1)))
			ft_error("Error! Failed to allocate memory.\n", arg, 0);
		ft_memcpy(arg->map[i], arr[i], ft_strlen(arr[i])+1);
		i++;
	}
	if (!(arg->map[n] = (char *)malloc(sizeof(char) * ft_strlen(line)+1)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0);
	ft_memcpy(arg->map[n], line, ft_strlen(line)+1);
	arg->map[n][ft_strlen(line)] = '\0';
	free_map(arr, n);
} 
int **ft_add_memory(int height, int width, int *arr_addr, int k, t_info *arg) //23 line
{
	int **arr_text;
	int i;
	int j;

	j = 0;
	i = 0;	
	if (!(arr_text = (int **)malloc(sizeof(int *) * height)))
		ft_error("Error! Failed to allocate memory.\n", arg, 0);
	while (i < height)
	{
		if (!(arr_text[i]= (int *)malloc(sizeof(int) * width)))
			ft_error("Error! Failed to allocate memory.\n", arg, 0);
		i++;
	}
	while(j < height)
	{
		i = 0;
		while(i < width)
		{
			arr_text[j][i] = arr_addr[k];
			i++;
			k++;
		}
		j++;
	}
	return (arr_text);
}
int **ft_parse_texture (char *path, t_info *arg) // 13 lines
{
	int **arr_text;
	int *arr_addr;
	int img_width;
	int img_height;
	t_mlx img;

	img.mlx = mlx_init();
	if (!(img.img = mlx_xpm_file_to_image(img.mlx, path, &img_width, &img_height)))
		ft_error("Error! wrong path to texture\n", arg, 0);
	arr_addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.length, &img.endian);
	arr_text = ft_add_memory(img_height, img_width, arr_addr, 0, arg); 
	mlx_destroy_image(img.mlx, img.img);
	free(img.mlx);
	//free(img.img);
	arr_addr = NULL;
	return (arr_text);
}
