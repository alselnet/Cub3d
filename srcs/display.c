/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/15 04:46:05 by aselnet          ###   ########.fr       */
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
	player_tile_y = floor(cub->dimensions[0] - cub->player.pos[1]);

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

void	draw_vertical_ray(t_cub * cub, t_img *img, double vector, t_ray ray)
{
	int	monitor;
	double y;

	y = 0;
	monitor = 0;
	while(!monitor)
	{
		draw_at_loc(0, y, cub, img);
		if (fabs(vector - PI * 0.5) < 0.0002)
		{
			if (y + cub->player.pos[1] >= ray.ray_y || y >= 8)
				monitor = 1;
			y += 0.001;
		}
		else if (fabs(vector - PI * 1.5) < 0.0002)
		{
			if (y + cub->player.pos[1] <= ray.ray_y || y <= -8)
				monitor = 1;
			y -= 0.001;
		}
		else
			break;
	}

}

void	draw_ray(t_cub *cub, t_img *img, double vector, t_ray ray)
{
	double	x;
	double	y;
	int		monitor;
	double	slope;

	x = 0;
	y = 0;
	slope = tan(vector);
	if (fabs(vector - PI * 1.5) < 0.0002 || fabs(vector - PI * 0.5) < 0.0002) // vertical
	{
		draw_vertical_ray(cub, img, vector, ray);
		return ;
	}
	monitor = 0;
	//printf ("slope is %f\n", slope);
	while(!monitor)
	{
		draw_at_loc(x, y, cub, img);
		if (vector < (PI * 0.5) || vector > PI * 1.5)
		{
			if (x + cub->player.pos[0] >= ray.ray_x)
				monitor = 1;
			x += 0.0001;
		}
		else
		{
		//	printf("hey\n");
			if (x + cub->player.pos[0] <= ray.ray_x)
				monitor = 1;
			x -= 0.0001;
		}
		if ((vector < PI && (y + cub->player.pos[1] >= ray.ray_y)) || (vector > PI && (cub->player.pos[1] + y <= ray.ray_y)) || x >= 8)
			monitor = 1;
		y = slope * x;
	}
}

void	draw_col(t_cub *cub, t_img *img, int col, t_ray ray)
{

	int	y;
	int	ceil;
	int	wall_h;
	(void) cub;
	(void) ceil;
	
	y = -1;
	wall_h = (int) (870) / ray.ray_len;
	if (wall_h > 870)
		wall_h = 870;
	//printf("wall_h is %d\n", wall_h);
	while (++y < ((870 - wall_h) / 2))
	{
		my_mlx_pixel_put(img, col, y, 0x000000);
	}
	ceil = y;
	// while (y < wall_h)
	// {
	// 	my_mlx_pixel_put(img, col, y, 0x0000cc);
	// 	y++;
	// }
	while (y < 870 - ceil)
	{
		my_mlx_pixel_put(img, col, y, 0x0000cc);
		y++;
	}
	while (y < 870)
	{
		my_mlx_pixel_put(img, col, y, 0x994c00);
		y++;
	}
	
}

void	draw_fov(t_cub *cub, t_img *img)
{
	double delta;
	t_ray	ray;
	int		col;
	int		corr_angle;

	delta = -0.8;
	col = 1151;
	// (void) ray;
	// (void) img;
	while (delta < 0.8)
	{
		ray = cast_ray(cub, cub->player.orientation + delta);
		draw_ray(cub, img, cub->player.orientation + delta, ray);
		corr_angle = cub->player.orientation;
		if (corr_angle < 0)
			corr_angle += 2 * PI;
		else if (corr_angle > 2 * PI)
			corr_angle -= 2 * PI;
		ray.ray_len = ray.ray_len * cos(delta);
		draw_col(cub, &cub->img3d, col, ray);
		delta += 0.00137;
		col--;
	}
	// t_ray	ray;
	// int		col;
	// printf("vector is %f * PI\n", cub->player.orientation/ PI);

	// col = 1152 / 2;
	// ray = cast_ray(cub, cub->player.orientation);
	// draw_ray(cub, img, cub->player.orientation, ray);
	// draw_col(cub, &cub->img3d, col, ray);
	return;
}

void	draw_player_start(t_cub *cub, t_img *img)
{
	fetch_player_start(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	printf("player orientation is %.2f\n", cub->player.orientation);
	draw_fov(cub, img);
}
