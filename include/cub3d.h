/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:05:09 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

# define PI 3.141592
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
	double	pos_x;
	double	pos_y;
	double	orientation;
}				t_player;

typedef struct	s_parsing
{
	char	*file;
	int	fd;
	char	**map;
	int	player_flag;
	int	width;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*lim_line;
}	t_parsing;

typedef struct s_cub {
	t_mlx	mlx;
	t_img	img;
	char	**map;
	char	*path;
	int		dimensions[2];
	int		res_x;
	int		res_y;
	t_player	player;
	t_parsing parsing;
}				t_cub;


//display.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_tile(t_img *img, int x, int y, int color);
void	draw_map(t_cub *cub, t_img *img);
void	draw_player_start(t_cub *cub, t_img *img);
void	draw_direction(t_cub *cub);
void	draw_ray(t_cub *cub, double vector, t_img *img);
void	draw_fov(t_cub *cub, t_img *img);

//init.c
void	init_mlx(t_cub *cub, int x, int y);
void	get_map_size(t_cub *cub);
void	fetch_map(t_cub *cub);

//utils.c
int	wclose(t_cub *cub);

//movement.c
int	exec_key(int keycode, t_cub *cub);

/*	PARSING */

//map_parsing.c
int	map_parsing(t_cub *cub);

//get_checking_map.c
int get_checking_map(t_parsing *data);

//check_map.c
int	check_bad_char(t_parsing *data);
int	check_map_player(t_parsing *data);
int	check_map_limits(t_parsing *data);

//parse_args.c
int	parse_args(int argc, char **argv, t_cub *cub);

//parse_utils.c
int	count_lines(char *file);
int	get_width(t_parsing *data);

//parse_infos.c
int	parse_infos(t_cub *cub);
void	free_parsing(t_parsing *data);

//set_card_path.c
int	set_no(char **buff, t_parsing *data);
int	set_so(char **buff, t_parsing *data);
int	set_ea(char **buff, t_parsing *data);
int	set_we(char **buff, t_parsing *data);

# endif