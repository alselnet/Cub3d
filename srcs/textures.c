/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:25:18 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/08 19:51:31 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures_ns(t_cub *cub)
{
	cub->img_wall_n.img = mlx_xpm_file_to_image(cub->mlx3d.mlx,
			"textures/bluestone.xpm", &cub->img_wall_n.width,
			&cub->img_wall_n.height);
	if (cub->img_wall_n.img)
		cub->img_wall_n.addr = mlx_get_data_addr(cub->img_wall_n.img,
				&cub->img_wall_n.bits_per_pixel, &cub->img_wall_n.line_length,
				&cub->img_wall_n.endian);
	cub->img_wall_s.img = mlx_xpm_file_to_image(cub->mlx3d.mlx,
			"textures/purplestone.xpm", &cub->img_wall_s.width,
			&cub->img_wall_s.height);
	if (cub->img_wall_s.img)
		cub->img_wall_s.addr = mlx_get_data_addr(cub->img_wall_s.img,
				&cub->img_wall_s.bits_per_pixel, &cub->img_wall_s.line_length,
				&cub->img_wall_s.endian);
}

void	load_textures_ew(t_cub *cub)
{	
	cub->img_wall_e.img = mlx_xpm_file_to_image(cub->mlx3d.mlx,
			"textures/greystone.xpm", &cub->img_wall_e.width,
			&cub->img_wall_e.height);
	if (cub->img_wall_e.img)
		cub->img_wall_e.addr = mlx_get_data_addr(cub->img_wall_e.img,
				&cub->img_wall_e.bits_per_pixel, &cub->img_wall_e.line_length,
				&cub->img_wall_e.endian);
	cub->img_wall_w.img = mlx_xpm_file_to_image(cub->mlx3d.mlx,
			"textures/colorstone.xpm", &cub->img_wall_w.width,
			&cub->img_wall_w.height);
	if (cub->img_wall_w.img)
		cub->img_wall_w.addr = mlx_get_data_addr(cub->img_wall_w.img,
				&cub->img_wall_w.bits_per_pixel, &cub->img_wall_w.line_length,
				&cub->img_wall_w.endian);
}

void	load_textures(t_cub *cub)
{
	load_textures_ns(cub);
	load_textures_ew(cub);
}	

int	set_texture_x(t_ray ray, t_img wall_texture)
{
	double	texture_x;

	if (ray.side == 'N' || ray.side == 'S')
		texture_x = (ray.ray_x - floor(ray.ray_x));
	else if (ray.side == 'E' || ray.side == 'W')
		texture_x = (ray.ray_y - floor(ray.ray_y));
	return ((int)(texture_x * wall_texture.width));
}

unsigned int	fetch_texture_px(t_cub *cub, t_ray ray, double i)
{
	t_img			wall_texture;
	unsigned int	color;
	int				texture_x;

	if (ray.side == 'N')
		wall_texture = cub->img_wall_n;
	else if (ray.side == 'S')
		wall_texture = cub->img_wall_s;
	else if (ray.side == 'E')
		wall_texture = cub->img_wall_e;
	else
		wall_texture = cub->img_wall_w;
	texture_x = set_texture_x(ray, wall_texture);
	color = my_mlx_pixel_get(&wall_texture, texture_x, (int)i);
	return (color);
}
