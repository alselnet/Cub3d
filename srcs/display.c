/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:31:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 21:07:56 by aselnet          ###   ########.fr       */
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

void	draw_stripe(t_cub *cub, t_img *img, int col, t_ray ray)
{
	int				x;
	int				ceil;
	unsigned int	color;
	int				i;

	x = -1;
	i = 0;
	ray.wall_h = (int)((870) / ray.ray_len);
	if (ray.wall_h > 870)
		ray.wall_h = 870;
	while (++x < ((870 - (int) ray.wall_h) / 2))
		my_mlx_pixel_put(img, col, x, 0x000000);
	ceil = x;
	while (x < 870 - ceil)
	{
		color = fetch_texture_px(cub, ray, i, 870 - (ceil * 2));
		my_mlx_pixel_put(img, col, x, color);
		x++;
		i++;
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
		draw_stripe(cub, &cub->img3d, col, ray);
		col--;
		delta += 0.001042;
	}
	return ;
}

void	draw_screen(t_cub *cub, t_img *img)
{
	(void) img;
	fetch_player_start(cub);
	load_textures(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	draw_3d(cub, -(FOV / 2));
}
