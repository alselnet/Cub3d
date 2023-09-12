/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/12 14:13:53 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.141592
# define MS 0.1
# define ROT_STEP 0.087266
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

//------------------------ STRUCT
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
typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	color;
}	t_rgb;

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
	int		c;
	int		f;
	char	*lim_line;
}	t_parsing;

typedef struct s_cub {
	t_mlx		mlx3d;
	t_img		img3d;
	t_img		img_wall_n;
	t_img		img_wall_s;
	t_img		img_wall_e;
	t_img		img_wall_w;
	char		**map;
	char		*path;
	int			dimensions[2];
	int			res_x;
	int			res_y;
	t_player	player;
	t_parsing parsing;
}				t_cub;

// -------------------------------------------- FUNCTIONS

//TMP
void			print_img(t_img wall_texture);
void			print_map(char *name, char **map);

//init.c
void			init_mlx(t_cub *cub, int x, int y);
void			get_map_size(t_cub *cub);
void			fetch_map(t_cub *cub);
void			fetch_player_starting_orientation(t_cub *cub);
void			fetch_player_start(t_cub *cub);

//init2.c
void			init_ray(t_ray *ray);

//utils.c
double			hyp_len(double x1, double x2, double y1, double y2);
unsigned int	my_mlx_pixel_get(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			correct_orientation(t_cub *cub);
int				ft_strlen_map(const char *s);

//close.c
int				wclose(t_cub *cub);

//raycasting.c
void			set_hray(t_cub *cub, t_ray *hray, double vector);
t_ray			horizontal_check_ray(t_cub *cub, double vector);
void			set_vray(t_cub *cub, t_ray *vray, double vector);
t_ray			vertical_check_ray(t_cub *cub, double vector);
t_ray			cast_ray(t_cub *cub, double vector);

//display.c
void			draw_at_loc(double x, double y, t_cub *cub, t_img *img);
void			draw_stripe(t_cub *cub, t_img *img, int col, t_ray ray);
void			draw_3d(t_cub *cub, double delta);
void			draw_screen(t_cub *cub, t_img *img);

//movement.c
void			refresh_img(t_cub *cub);
int				check_wall_player(double x, double y, t_cub *cub);
int				exec_key(int keycode, t_cub *cub);

//movement2.c
void			rotate(char dir, t_cub *cub);
int				check_strafe(char dir, t_cub *cub);
void			strafe(char dir, t_cub *cub);
int				check_move(char dir, t_cub *cub);
void			move(char dir, t_cub *cub);

//textures.c
void			load_textures_ns(t_cub *cub);
void			load_textures_ew(t_cub *cub);
void			load_textures(t_cub *cub);
int				set_texture_x(t_ray ray, t_img wall_texture);
unsigned int	fetch_texture_px(t_cub *cub, t_ray ray, double i);

//minimap.c
void			draw_vertical_ray(t_cub *cub, t_img *img,
					double vector, t_ray ray);
void			draw_ray(t_cub *cub, t_img *img, double vector, t_ray ray);
void			draw_tile(t_img *img, int y, int x, int color);
void			draw_map(t_cub *cub, t_img *img);
void			draw_minimap(t_cub *cub, t_img *img, double delta);

//destroy_all.c
void	free_parsing(t_parsing *data);
void	destroy_all(t_cub *cub);

/*	PARSING */

//map_parsing.c
int		map_parsing(t_cub *cub);

//get_checking_map.c
int 	get_checking_map(t_parsing *data, t_cub *cub);

//get_checking_map_2.c
void	fill_line(char *map, char *line, t_parsing *data);
char	*fill_bot_limit(char *prev);

//check_map.c
int		check_bad_char(t_parsing *data);
int		check_map_player(t_parsing *data);
int		check_map_limits(t_parsing *data);

//parse_args.c
int		parse_args(int argc, char **argv, t_cub *cub);

//parse_utils.c
int		count_lines(t_parsing *data);
int		get_width(t_parsing *data);
int		go_to_map(t_parsing *data, t_cub *cub);
void	skip_empty_lines(char *line, int fd);

//parse_infos.c
int		parse_infos(t_cub *cub);
void	free_parsing(t_parsing *data);

//set_card_path.c
int		set_no(char **buff, t_parsing *data);
int		set_so(char **buff, t_parsing *data);
int		set_ea(char **buff, t_parsing *data);
int		set_we(char **buff, t_parsing *data);

//set_rgb.c
int		set_rgb(char *str);

# endif
