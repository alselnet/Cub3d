/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 18:23:01 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && y >= 0 && x < 1152 && y < 870))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_img *img, int x, int y, int color)
{
	int	a;
	int	b;

	a = x*50;
	while (a < (x + 1) * 50)
	{
		b = y*50;
		while (b < (y + 1) * 50)
		{
			my_mlx_pixel_put(img, b, a, color);
			b++;
		}
		a++;
	}
}

void	draw_map(t_cub *cub, t_img *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < ft_arr_len(cub->map))
	{
		y = 0;
		while (y < (int)ft_strlen(cub->map[x]))
		{
			if (ft_isinbase(cub->map[x][y], "0NSEW"))
				draw_tile(img, x, y, 0xfff0f6);
			else if (cub->map[x][y] == '1')
				draw_tile(img, x, y, 0xfa6339);
			y++;
		}
		x++;
	}
}

void	define_dir (t_cub *cub)
{
	cub->player.dir[0] = (VIS_DIST * cos(cub->player.orientation)); 
	cub->player.dir[1] = (VIS_DIST * sin(cub->player.orientation)); 
}

void	fetch_player_starting_orientation(t_cub *cub)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = floor(cub->player.pos[0]);
	player_tile_y = floor(cub->player.pos[1]);

	if (cub->map[player_tile_x][player_tile_y] == 'W')
		cub->player.orientation = PI * 0.5;
	else if (cub->map[player_tile_x][player_tile_y] == 'N')
		cub->player.orientation = 2 * PI;
	else if (cub->map[player_tile_x][player_tile_y] == 'E')
		cub->player.orientation = PI * 1.5;
	else if (cub->map[player_tile_x][player_tile_y] == 'S')
		cub->player.orientation =  PI;
	define_dir(cub);
}

void	fetch_player_start(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while(cub->map[x])
	{
		y = 0;
		while (cub->map[x][y])
		{
			if(ft_isinbase(cub->map[x][y], "NSEW"))
			{
				cub->player.pos[0] = x;
				cub->player.pos[1] = y;
				fetch_player_starting_orientation(cub);
				cub->player.pos[0] += 0.5;
				cub->player.pos[1] += 0.5;
				return;
			}
			y++;
		}
		x ++;
	}
}
void	draw_vertical_ray(t_cub * cub, double vector, t_img *img)
{
	int	x_px;
	int	y_px;

	x_px = cub->player.pos[0] * 50;
	y_px = cub->player.pos[1] * 50;
	while(cub->map[x_px / 50][y_px / 50] != '1')
	{
		my_mlx_pixel_put(img, y_px, x_px, 0xdd001c);
		if ((vector > (PI * 0.4982) && vector < (PI * 0.50018)))
		//if ((vector == PI * 0.5))
			y_px--;
		// else if ((vector == PI * 1.5))
		else if ((vector > (PI * 1.4982) && vector < (PI * 1.50018)))
			y_px++;
		else
			break;
	}

}

void	draw_ray(t_cub *cub, double vector, t_img *img)
{
	double	x;
	double	y;
	int		x_px;
	int		y_px;
	int		monitor;
	double	slope;

	x = 0;
	y = 0;
	monitor = 0;
	x_px = cub->player.pos[0] * 50;
	y_px = cub->player.pos[1] * 50;
	if ((vector > (PI * 0.4982) && vector < (PI * 0.50018))
	|| (vector > (PI * 1.4982) && vector < (PI * 1.50018)))
	// if ((vector == (PI * 0.5))
	// || (vector == (PI * 1.5)))	
	{
		draw_vertical_ray(cub, vector, img);
		return;
	}

	slope = tan(vector);
	//printf ("slope is %f\n", slope);
	while(!monitor)
	{
		my_mlx_pixel_put(img, y_px, x_px, 0xdd001c);
		if (vector > (PI * 0.5) && vector < PI * 1.5)
			x += 0.001;
		else 
			x -= 0.001;
		y = slope * x;
		x_px = (x + cub->player.pos[0]) * 50;
		y_px = (y + cub->player.pos[1]) * 50;
		//if ((x_px % 50) <=  2 || (y_px % 50) <= 2 || (x_px % 50) >= 47 || (y_px % 50) >= 47)
		//{
			if (cub->map[x_px / 50][y_px / 50] == '1')
			{
				monitor = 1;
				//if (x_px % 50 != 0 && x_px % 50 != 49 && y_px % 50 != 0 && y_px % 50 != 49)
				//printf("PROBLEM\n");
				// printf("ray hit the wall at pixel x = %d\n", x_px % 50);
				// printf("ray hit the wall at pixel y = %d\n", y_px % 50);
			}
		//}

	}
}

void	draw_fov(t_cub *cub, t_img *img)
{
	double delta;

	delta = 0.001839;
	//delta = 0.01;
	draw_ray(cub, cub->player.orientation, img);
	while (delta < 0.8)
	{
		draw_ray(cub, cub->player.orientation + delta, img);
		delta += 0.001839;
		//delta += 0.01;
	}
	while (delta > 0)
	{
		draw_ray(cub, cub->player.orientation - delta, img);
		delta -= 0.001839;
		//delta -= 0.01;
	}
}

void	draw_player_start(t_cub *cub, t_img *img)
{
	fetch_player_start(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	printf("player orientation is %f\n", cub->player.orientation);
	draw_fov(cub, img);
}
