/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:31:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:02:42 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_at_loc(double x, double y, t_cub *cub, t_img *img)
{
	int	x_px;
	int	y_px;

	x_px = (x + cub->player.pos[0]) * 50;
	y_px = (cub->dimensions[0] - (y + cub->player.pos[1])) * 50;
	my_mlx_pixel_put(img, x_px, y_px, 0xdd001c);
}

// void	color_wall_pixel(t_cub *cub, t_ray ray)
// {
// 	__uint32_t	color;
// 	double	wall_x;
// 	double	wall_y;

// 	if (ray.side == 'N' || ray.side == 'S')

// 	else if (ray,side == 'W' || ray.side == 'E')

// }

void	draw_stripe(t_cub *cub, t_img *img, int col, t_ray ray)
{
	int	x;
	int	ceil;

	x = -1;
	(void) ceil;
	(void) cub;
	ray.wall_h = (int)((870) / ray.ray_len);
	if (ray.wall_h > 870)
		ray.wall_h = 870;
	while (++x < ((870 - (int) ray.wall_h) / 2))
	{
		my_mlx_pixel_put(img, col, x, 0x000000);
	}
	ceil = x;
	while (x < 870 - ceil)
	{
		// color_wall_pixel(cub, ray); WITH TEXTURE
		my_mlx_pixel_put(img, col, x, 0x0000cc);
		x++;
	}
	while (x < 870)
	{
		my_mlx_pixel_put(img, col, x, 0x994c00);
		x++;
	}
}

void	draw_3d(t_cub *cub, double delta)
{
	t_ray	ray;
	int		col;
	int		i;
	double	angle;

	col = 1151;
	while (delta <= 0.6)
	{
		angle = cub->player.orientation + delta;
		if (angle < 0)
			angle += 2 * PI;
		else if (angle > 2 * PI)
			angle -= 2 * PI;
		ray = cast_ray(cub, angle);
		ray.ray_len = ray.ray_len * cos(delta);
		i = 5;
		while (--i > 0)
		{
			draw_stripe(cub, &cub->img3d, col, ray);
			col--;
		}
		delta += 0.004166667;
	}
	return ;
}

void	draw_screen(t_cub *cub, t_img *img)
{
	(void) img; // minimap
	fetch_player_start(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	//printf("player orientation is %.2f\n", cub->player.orientation);
	draw_3d(cub, -(FOV / 2));
	//draw_minimap(cub, img, delta); // minimap
}
