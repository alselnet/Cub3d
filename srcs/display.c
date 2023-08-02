/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/02 17:22:59 by aselnet          ###   ########.fr       */
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

void	draw_map(t_cub *cub)
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
				draw_tile(&cub->img, x, y, 0xfff0f6);
			else if (cub->map[y][x] == '1')
				draw_tile(&cub->img, x, y, 0xfa6339);
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
		cub->player.direction = PI / 2;
	else if (cub->map[player_tile_x][player_tile_y] == 'E')
		cub->player.direction = 2 * PI;
	else if (cub->map[player_tile_x][player_tile_y] == 'S')
		cub->player.direction = 3 * PI / 2;
	else if (cub->map[player_tile_x][player_tile_y] == 'W')
		cub->player.direction = PI;
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
				printf("player pos_x is %f\n", cub->player.pos_x);
				printf("player pos_y is %f\n", cub->player.pos_y);
				fetch_player_starting_orientation(cub);
				return;
			}
			x++;
		}
		y ++;
	}
}
void	draw_vertical_ray(t_cub * cub)
{
	int	x_px;
	int	y_px;

	x_px = cub->player.pos_x * 50;
	y_px = cub->player.pos_y * 50;
	while(cub->map[y_px / 50][x_px / 50] != '1')
	{
		my_mlx_pixel_put(&cub->img, x_px, y_px, 0xdd001c);
		if (cub->player.direction == PI / 2)
			y_px--;
		else
			y_px++;
	}

}

void	draw_ray(t_cub *cub)
{
	double	x;
	double	y;
	int		x_px;
	int		y_px;
	double	slope;

	x = 0;
	y = 0;
	x_px = cub->player.pos_x * 50;
	y_px = cub->player.pos_y * 50;
	if (cub->player.direction == PI / 2 || cub->player.direction == PI * 3 / 2)
	{
		draw_vertical_ray(cub);
		return;
	}

	slope = tan(cub->player.direction);
	printf ("slope is %f\n", slope);
	while(cub->map[y_px / 50][x_px / 50] != '1')
	{
		my_mlx_pixel_put(&cub->img, x_px, y_px, 0xdd001c);
		if (cub->player.direction > PI / 2 && cub->player.direction < PI * 3 / 2)
			x += 0.02;
		else 
			x -= 0.02;
		y = slope * x;
		x_px = (x + cub->player.pos_x) * 50;
		y_px = (y + cub->player.pos_y) * 50;
	}
}

void	draw_player_start(t_cub *cub)
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
			my_mlx_pixel_put(&cub->img, a, b, 0x000000);
			a++;
		}
		b++;
	}
	printf("player orientation is %f\n", cub->player.direction);
	draw_ray(cub);
}
