/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosemar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:29:48 by jrosemar          #+#    #+#             */
/*   Updated: 2020/10/27 14:29:50 by jrosemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"
#include <stdio.h>
# include "../LIBFT/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#define SIZE 1024
#define W 1731
#define S 1753
#define A 1734
#define D 1751
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364


typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int length;
	int endian;

}			t_mlx;

typedef struct s_player
{
	double x;
	double y;
	double corner;
	double start;
	double end;
}		t_player;

typedef struct s_texture
{
	int **north_tex; //free
	int **south_tex; //free
	int **west_tex; //free
	int **east_tex; //free
	int **sprite; //free
	int spr_width; 
	int spr_height;

}	t_text;

typedef struct s_sprite
{
	double x;
	double y;
	double corner;
	double dist;
	double len;
	double x_start;
	double y_start;
	double width;
	double height;
	struct s_sprite *next;

} t_sprite;

typedef struct s_cross
{
	double x;
	double y;
	double delta_x;
	double delta_y;
	
}			t_cross;

typedef struct s_paint
{
	int y;
	double x1;
	double y1;
	int i;
	double h;
	int d;
	int k;
	double scale;
	double distanse;
	int floor;
	int cell;
}				t_paint;

typedef struct	s_map
{
	char *map;
	int x;
	int y;
}				t_map;

typedef struct s_info
{
	int res[2];
	char *north; //free
	char *south; //free
	char *west; //free
	char *east; //free
	char *sprite; //free
	int floor[3];
	int cel[3];
	int error;
	char **map;
	int flag;
	int mp; //количество строк в сhar **map
	int pm;//количество столбцов в сhar **map
	t_player player;
	t_mlx cub;
	t_text text;
	int arr [1920];
	double corner [1920];
	double cor_pl [1920];
	int coor_x [1920];
	int coor_y [1920]; //выделить память по ширине окна
	char cross[1920]; 
	t_sprite *spr;
}				t_info;

int get_next_line(int fd, char **line);
void ft_get_resolution(char *line, t_info *arg, int n);
char  *ft_get_path(char *line, t_info *arg);
void ft_get_floor(char *line, t_info *arg);
void ft_get_celling(char *line, t_info *arg);
void ft_parse_file(t_info *arg, int fd);
t_info ft_init_info(int flag);
void ft_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int ft_check_sym(char *str, char c);
void ft_check_map3(char **map, t_info *arg, int max);
void ft_check_map2(char **map, t_info *arg, int max, int i, int j);
void ft_check_map (char **map, t_info *arg, int x, int y, int max);
t_sprite **ft_unite_sprite(t_sprite *sprt, int n, t_info *arg);
void ft_create_sprite(int x, int y, t_info *arg);
void ft_find_sprites(t_info *arg);
void ft_parse_map(char *line, int n, t_info *arg);
int **ft_parse_texture (char *path, t_info *arg);
t_player ft_find_player(t_info *arg);
void	ft_sort_sprite(t_info *arg, int i);
int		ft_get_color(t_info *arg, double h, double w);
void	ft_draw_sprite2(t_info *arg, t_sprite *sprite, int i, int j);
void ft_draw_sprite(t_info *arg);
int ft_draw_3d(t_info *arg);
int ft_cross_map(t_info *arg, double x, double y);
double ft_cross_x(t_info *arg, double corner, t_cross *rs, int n);
double ft_cross_y(t_info *arg, double corner, t_cross *rs, int n);
int ft_put_ray(t_info *arg);
int ft_keypress(int keycode, t_info *arg);
int ft_check_main_arguments(int argc, char **argv);
int **ft_parse_sprite (char *path, t_info *arg);
int ft_read_file(char *filename, t_info *arg, int flag);
void ft_moveupdown(t_info *arg, int key);
void ft_moverightleft(t_info *arg, int key);
double ft_find_dist(t_info *arg, t_cross cr, t_cross *rs);
int **ft_add_memory(int height, int width, int *arr_addr, int k, t_info *arg);
void ft_check_map4(char **map, t_info *arg, int i, int j);
void ft_init_player(t_player *player, char c, double x, double y);
void ft_fill_bmp(char *bmp, int num, int size, t_info *arg);
void free_map(char **arr, int h);
int exit_game(int key, t_info *arg);
void ft_error(char *str, t_info *arg, int mistake);
int main(int argc, char **argv);

















#endif
