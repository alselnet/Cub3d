/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/03 00:39:41 by aselnet          ###   ########.fr       */
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

	b = y*50;
	while (b < (y + 1) * 50)
	{
		a = x*50;
		while (a < (x + 1) * 50)
		{
			my_mlx_pixel_put(img, a, b, color);
			a++;
		}
		b++;
	}
}

void	draw_map(t_cub *cub, t_img *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < ft_arr_len(cub->map))
	{
		while (x < (int)ft_strlen(cub->map[y]))
		{
			if (ft_isinbase(cub->map[y][x], "0NSEW"))
				draw_tile(img, x, y, 0xfff0f6);
			else if (cub->map[y][x] == '1')
				draw_tile(img, x, y, 0xfa6339);
			x++;
		}
		x = 0;
		y++;
	}
}

void	fetch_player_starting_orientation(t_cub *cub)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = floor(cub->player.pos_x);
	player_tile_y = floor(cub->player.pos_y);

	if (cub->map[player_tile_x][player_tile_y] == 'N')
		cub->player.orientation = PI / 2;
	else if (cub->map[player_tile_x][player_tile_y] == 'E')
		cub->player.orientation = 2 * PI;
	else if (cub->map[player_tile_x][player_tile_y] == 'S')
		cub->player.orientation = 3 * PI / 2;
	else if (cub->map[player_tile_x][player_tile_y] == 'W')
		cub->player.orientation = PI;
}

void	fetch_player_start(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while(cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if(ft_isinbase(cub->map[y][x], "NSEW"))
			{
				cub->player.pos_x = x + 0.5;
				cub->player.pos_y = y + 0.5;
				fetch_player_starting_orientation(cub);
				return;
			}
			x++;
		}
		y ++;
	}
}
void	draw_vertical_ray(t_cub * cub, double vector, t_img *img)
{
	int	x_px;
	int	y_px;

	x_px = cub->player.pos_x * 50;
	y_px = cub->player.pos_y * 50;
	while(cub->map[y_px / 50][x_px / 50] != '1')
	{
		my_mlx_pixel_put(img, x_px, y_px, 0xdd001c);
		if ((vector > (PI * 0.499) && vector < (PI * 0.501)))
			y_px--;
		else if ((vector > (PI * 1.499) && vector < (PI * 1.501)))
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
	x_px = cub->player.pos_x * 50;
	y_px = cub->player.pos_y * 50;
	if ((vector > (PI * 0.499) && vector < (PI * 0.501))
	|| (vector > (PI * 1.499) && vector < (PI * 1.501)))
	{
		draw_vertical_ray(cub, vector, img);
		return;
	}

	slope = tan(vector);
	//printf ("slope is %f\n", slope);
	while(!monitor)
	{
		my_mlx_pixel_put(img, x_px, y_px, 0xdd001c);
		if (vector > (PI * 0.5) && vector < PI * 1.5)
			x += 0.001;
		else 
			x -= 0.001;
		y = slope * x;
		x_px = (x + cub->player.pos_x) * 50;
		y_px = (y + cub->player.pos_y) * 50;
		//if ((x_px % 50) <=  2 || (y_px % 50) <= 2 || (x_px % 50) >= 47 || (y_px % 50) >= 47)
		//{
			if (cub->map[y_px / 50][x_px / 50] == '1')
				monitor = 1;
		//}

	}
}

void	draw_fov(t_cub *cub, t_img *img)
{
	double delta;

	delta = 0.0023;
	draw_ray(cub, cub->player.orientation, img);
	while (delta < 0.8)
	{
		draw_ray(cub, cub->player.orientation + delta, img);
		delta += 0.0023;
	}
	while (delta > 0)
	{
		draw_ray(cub, cub->player.orientation - delta, img);
		delta -= 0.0023;
	}
}

void	draw_player_start(t_cub *cub, t_img *img)
{
	int	a;
	int	b;

	fetch_player_start(cub);
	if (!cub->player.pos_x || !cub->player.pos_y)
		return ;
	b = (cub->player.pos_y*50) - 9;
	while (b < (cub->player.pos_y*50) + 10 + 1)
	{
		a = (cub->player.pos_x*50) - 9;
		while (a < (cub->player.pos_x*50) + 10 + 1)
		{
			my_mlx_pixel_put(img, a, b, 0x000000);
			a++;
		}
		b++;
	}
	//printf("player orientation is %f\n", cub->player.orientation);
	draw_fov(cub, img);
}
