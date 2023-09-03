/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:25:18 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:47:50 by aselnet          ###   ########.fr       */
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
			"textures/greystone.xpm", &cub->img_wall_n.width,
			&cub->img_wall_n.height);
	if (cub->img_wall_e.img)
		cub->img_wall_e.addr = mlx_get_data_addr(cub->img_wall_e.img,
				&cub->img_wall_n.bits_per_pixel, &cub->img_wall_n.line_length,
				&cub->img_wall_n.endian);
	cub->img_wall_w.img = mlx_xpm_file_to_image(cub->mlx3d.mlx,
			"textures/colorstone.xpm", &cub->img_wall_n.width,
			&cub->img_wall_n.height);
	if (cub->img_wall_w.img)
		cub->img_wall_w.addr = mlx_get_data_addr(cub->img_wall_e.img,
				&cub->img_wall_n.bits_per_pixel, &cub->img_wall_n.line_length,
				&cub->img_wall_n.endian);
}

// void	color_wall_pixel(t_cub *cub, t_ray ray)
// {
// 	__uint32_t	color;
// 	double	wall_x;
// 	double	wall_y;

// 	if (ray.side == 'N' || ray.side == 'S')

// 	else if (ray,side == 'W' || ray.side == 'E')

// }

void	load_textures(t_cub *cub)
{
	load_textures_ns(cub);
	load_textures_ew(cub);
}	
