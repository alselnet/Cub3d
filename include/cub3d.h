/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:21:21 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

# define PI 3.141592
# define MS 0.1
# define ROT_STEP PI / 36
# define VIS_DIST 1
# define FOV 1.2
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>

typedef struct s_mlx {
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_player{

	double	pos[2];
	double	orientation;
}				t_player;

typedef struct s_ray
{
	char	side;
	int		wall_h;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	ray_len;
	double	max_view;
}				t_ray;

typedef struct s_cub {
	t_mlx	mlx;
	t_mlx	mlx3d;
	t_img	img;
	t_img	img3d;
	t_img	img_wall_n;
	t_img	img_wall_s;
	t_img	img_wall_e;
	t_img	img_wall_w;
	char	**map;
	char	*path;
	int		dimensions[2];
	int		res_x;
	int		res_y;
	t_player	player;
}				t_cub;


//display.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_tile(t_img *img, int x, int y, int color);
void	draw_at_loc(double x, double y, t_cub *cub, t_img *img);
void	draw_map(t_cub *cub, t_img *img);
void	fetch_player_start(t_cub *cub);
void	draw_player_start(t_cub *cub, t_img *img);
void	draw_direction(t_cub *cub);
void	draw_ray(t_cub *cub, t_img *img, double vector, t_ray ray);
void	draw_screen(t_cub *cub, t_img *img);
void	draw_3d(t_cub *cub, double delta);
void	draw_minimap(t_cub *cub, t_img *img, double delta);
void	define_dir (t_cub *cub);

//init.c
unsigned int	my_mlx_pixel_get(t_img *img, int x, int y);
void	init_mlx(t_cub *cub, int x, int y);
void	get_map_size(t_cub *cub);
void	fetch_map(t_cub *cub);

//utils.c
void	correct_orientation(t_cub *cub);
int	wclose(t_cub *cub);
double	hyp_len(double x1, double x2, double y1, double y2);
int	check_wall_player(double x, double y, t_cub *cub);

//movement.c
int	exec_key(int keycode, t_cub *cub);
void	refresh_img(t_cub *cub);

//movement2.c
void	rotate(char dir, t_cub *cub);
void	strafe(char dir, t_cub *cub);
void	move(char dir, t_cub *cub);

//raycasting.c
t_ray	cast_ray(t_cub *cub, double vector);

# endif