/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 16:56:35 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

# define PI 3.141592
# define DELTA 1
# define MS 0.1
# define ROT_STEP PI / 36
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
}				t_img;

typedef struct s_player{

	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	orientation;
}				t_player;

typedef struct s_cub {
	t_mlx	mlx;
	t_img	img;
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
void	draw_map(t_cub *cub, t_img *img);
void	draw_player_start(t_cub *cub, t_img *img);
void	draw_direction(t_cub *cub);
void	draw_ray(t_cub *cub, double vector, t_img *img);
void	draw_fov(t_cub *cub, t_img *img);
void	define_dir (t_cub *cub);

//init.c
void	init_mlx(t_cub *cub, int x, int y);
void	get_map_size(t_cub *cub);
void	fetch_map(t_cub *cub);

//utils.c
int	wclose(t_cub *cub);

//movement.c
int	exec_key(int keycode, t_cub *cub);

# endif