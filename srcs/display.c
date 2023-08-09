/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/09 23:38:22 by aselnet          ###   ########.fr       */
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

void	draw_tile(t_img *img, int y, int x, int color)
{
	int	a;
	int	b;

	a = y*50;
	while (a < (y + 1) * 50)
	{
		b = x*50;
		while (b < (x + 1) * 50)
		{
			my_mlx_pixel_put(img, b, a, color);
			b++;
		}
		a++;
	}
}

void	draw_map(t_cub *cub, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_arr_len(cub->map))
	{
		j = 0;
		while (j < (int)ft_strlen(cub->map[i]))
		{
			if (ft_isinbase(cub->map[i][j], "0NSEW"))
				draw_tile(img, i, j, 0xfff0f6);
			else if (cub->map[i][j] == '1')
				draw_tile(img, i, j, 0xfa6339);
			j++;
		}
		i++;
	}
}

void	fetch_player_starting_orientation(t_cub *cub)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = floor(cub->player.pos[0]);
	player_tile_y = floor(cub->player.pos[1]);

	if (cub->map[player_tile_y][player_tile_x] == 'W')
		cub->player.orientation = PI;
	else if (cub->map[player_tile_y][player_tile_x] == 'N')
		cub->player.orientation = PI * 0.5;
	else if (cub->map[player_tile_y][player_tile_x] == 'E')
		cub->player.orientation = 0;
	else if (cub->map[player_tile_y][player_tile_x] == 'S')
		cub->player.orientation =  PI * 1.5;
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
				cub->player.pos[0] = x;
				cub->player.pos[1] = cub->dimensions[0] - y;
				fetch_player_starting_orientation(cub);
				cub->player.pos[0] += 0.5;
				cub->player.pos[1] -= 0.5;
				return;
			}
			x++;
		}
		y ++;
	}
}
void	draw_at_loc(double x, double y, t_cub *cub, t_img *img)
{
	int	x_px;
	int y_px;

	x_px = (x + cub->player.pos[0]) * 50;
	y_px = (cub->dimensions[0] - (y + cub->player.pos[1])) * 50;
	my_mlx_pixel_put(img, x_px, y_px, 0xdd001c);
}
void	draw_vertical_ray(t_cub * cub, double vector, t_img *img)
{
	double y;

	y = 0;
	while(cub->map[(int)(cub->dimensions[0] - (y + cub->player.pos[1]))][(int)(cub->player.pos[0])] != '1')
	{
		draw_at_loc(0, y, cub, img);
		if ((vector > (PI * 0.4982) && vector < (PI * 0.50018)))
		//if ((vector == PI * 0.5))
			y += 0.001;
		// else if ((vector == PI * 1.5))
		else if ((vector > (PI * 1.4982) && vector < (PI * 1.50018)))
			y -= 0.001;
		else
			break;
	}

}

void	draw_ray(t_cub *cub, double vector, t_img *img)
{
	double	x;
	double	y;
	int		monitor;
	double	slope;

	x = 0;
	y = 0;
	monitor = 0;
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
		draw_at_loc(x, y, cub, img);
		if (vector < (PI * 0.5) || vector > PI * 1.5)
			x += 0.001;
		else
			x -= 0.001;
		y = slope * x;
		//if ((x_px % 50) <=  2 || (y_px % 50) <= 2 || (x_px % 50) >= 47 || (y_px % 50) >= 47)
		//{
			if (cub->map[(int)(cub->dimensions[0] - (y + cub->player.pos[1]))][(int)(x + cub->player.pos[0])] == '1')
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
double	round_to_nearest_50(double number)
{
	double	quotient;
	double	nearest_multiple;

	quotient = number / 50.0;
	nearest_multiple = round(quotient) * 50.0;
	if (fabs(number - nearest_multiple) < 25.0)
        return nearest_multiple;
	else if (number < nearest_multiple)
        return nearest_multiple - 50.0;
	else 
        return nearest_multiple + 50.0;

}

void	cast_ray(t_cub *cub, double vector, t_img *img)
{
	int		map_x;
	int		map_y;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	delta_o;

	map_x = 0;
	map_y = 0;
	ray_x = 0;
	ray_y = 0;
	delta_x = 0;
	delta_y = 0;
	delta_o = 0;
	(void) img;
	(void) map_x;
	(void) map_y;
	(void) delta_o;
	printf("vector is %.2f\n", vector);
	if (vector > PI)
	{
		printf("cub->player.pos[0] is %.2f\n", cub->player.pos[0]);
		printf("cub->player.pos[1] is %.2f\n", cub->player.pos[1]);
		ray_y = (double)round(cub->player.pos[1]) - 1.0001;
		ray_x = (((double)round(cub->player.pos[1]) - cub->player.pos[1] - 1)/ tan(vector)) + cub->player.pos[0];
		delta_y = -1;
		delta_x = delta_y / tan(vector);
		printf("ray_x is %.2f\n", ray_x);
		printf("ray_y is %.2f\n", ray_y);
		printf("delta_x is %.2f\n", delta_x);
		printf("delta_y is %.2f\n", delta_y);
	}
	else if (vector < PI)
	{
		printf("cub->player.pos[0] is %.2f\n", cub->player.pos[0]);
		printf("cub->player.pos[1] is %.2f\n", cub->player.pos[1]);
		ray_y = (double)round(cub->player.pos[1]) + 0.0001;
		ray_x = (((double)round(cub->player.pos[1]) - cub->player.pos[1])/ tan(vector)) + cub->player.pos[0];
		delta_y = 1;
		delta_x = delta_y / tan(vector);
		printf("ray_x is %.2f\n", ray_x);
		printf("ray_y is %.2f\n", ray_y);
		printf("delta_x is %.2f\n", delta_x);
		printf("delta_y is %.2f\n", delta_y);
	}
	else if (vector == 0.00 || vector == PI)
	{
		ray_x = cub->player.pos[0];
		ray_y = 0;
		delta_o = 8;
		printf("ray_x is %.2f\n", ray_x);
		printf("ray_y is %.2f\n", ray_y);
	}
	// while (delta_o < 8)
	// {
	// 	map_x = (int) ray_x;
	// 	if ()
	// }

}

void	draw_fov(t_cub *cub, t_img *img)
{
	// double delta;

	// delta = 0.001839;
	// //delta = 0.01;
	// draw_ray(cub, cub->player.orientation, img);
	// while (delta < 0.8)
	// {
	// 	draw_ray(cub, cub->player.orientation + delta, img);
	// 	delta += 0.001839;
	// 	//delta += 0.01;
	// }
	// while (delta > 0)
	// {
	// 	draw_ray(cub, cub->player.orientation - delta, img);
	// 	delta -= 0.001839;
	// 	//delta -= 0.01;
	// }
	cast_ray(cub, cub->player.orientation, img);
	draw_ray(cub, cub->player.orientation, img);
	return;
}

void	draw_player_start(t_cub *cub, t_img *img)
{
	fetch_player_start(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	printf("player orientation is %f\n", cub->player.orientation);
	(void) img;
	draw_fov(cub, img);
}
