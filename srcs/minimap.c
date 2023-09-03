/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:34:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:30:32 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_ray(t_cub *cub, t_img *img, double vector, t_ray ray)
{
	int		monitor;
	double	y;

	y = 0;
	monitor = 0;
	while (!monitor)
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
			break ;
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
	if (fabs(vector - PI * 1.5) < 0.0002 || fabs(vector - PI * 0.5) < 0.0002)
	{
		draw_vertical_ray(cub, img, vector, ray);
		return ;
	}
	monitor = 0;
	while (!monitor)
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
			if (x + cub->player.pos[0] <= ray.ray_x)
				monitor = 1;
			x -= 0.0001;
		}
		if ((vector < PI && (y + cub->player.pos[1] >= ray.ray_y))
			|| (vector > PI && (cub->player.pos[1] + y <= ray.ray_y)) || x >= 8)
			monitor = 1;
		y = slope * x;
	}
}

void	draw_tile(t_img *img, int y, int x, int color)
{
	int	a;
	int	b;

	a = y * 50;
	while (a < (y + 1) * 50)
	{
		b = x * 50;
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

void	draw_minimap(t_cub *cub, t_img *img, double delta)
{
	t_ray	ray;
	double	angle;

	while (delta <= 0.6)
	{
		angle = cub->player.orientation + delta;
		if (angle < 0)
			angle += 2 * PI;
		else if (angle > 2 * PI)
			angle -= 2 * PI;
		ray = cast_ray(cub, angle);
		draw_ray(cub, img, angle, ray); //MINIMAP
		delta += 0.004166667;
	}
}
