/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:31:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/12 19:56:58 by jthuysba         ###   ########.fr       */
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
	double			i;
	int				wall_h;
	double			i_offset;

	x = -1;
	i_offset = 0;
	wall_h = 870;
	ray.wall_h = (int)((870) / ray.ray_len);
	if (ray.wall_h > 870)
		i_offset = (ray.wall_h - 870) / 2.0;
	else
		wall_h = ray.wall_h;
	while (++x < ((870 - (int) wall_h) / 2))
		my_mlx_pixel_put(img, col, x, cub->parsing.c);
	i = i_offset * ((64.0 / (double)(ray.wall_h)));
	while (x < (870 + (int)wall_h) / 2)
	{
		my_mlx_pixel_put(img, col, x, fetch_texture_px(cub, ray, i));
		x++;
		i += (64.0 / (double)(ray.wall_h));
	}
	x--;
	while (++x < 870)
		my_mlx_pixel_put(img, col, x, cub->parsing.f);
}

void	draw_3d(t_cub *cub, double delta)
{
	t_ray	ray;
	int		col;
	double	angle;

	col = 1151;
	while (delta <= ((double)FOV / 2.0))
	{
		angle = cub->player.orientation + delta;
		if (angle < 0)
			angle += 2.0 * PI;
		else if (angle > 2 * PI)
			angle -= 2.0 * PI;
		ray = cast_ray(cub, angle);
		ray.ray_len = ray.ray_len * cos(delta);
		draw_stripe(cub, &cub->img3d, col, ray);
		col--;
		delta += ((double) FOV / 1152.0);
	}
	return ;
}

void	draw_screen(t_cub *cub, t_img *img)
{
	(void) img;
	get_map_size(cub);
	fetch_player_start(cub);
	load_textures(cub);
	if (!cub->player.pos[0] || !cub->player.pos[1])
		return ;
	draw_3d(cub, -((double)FOV / 2.0));
}
