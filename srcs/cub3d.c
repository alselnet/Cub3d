/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 15:45:52 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

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

void	load_textures(t_cub *cub)
{
	load_textures_ns(cub);
	load_textures_ew(cub);
}			

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (0);
	cub.path = ft_strjoin("maps/", argv[1]);
	if (!cub.path)
		return (0);
	init_mlx(&cub, 1152, 870);
	load_textures(&cub);
	fetch_map(&cub);
	if (!cub.map)
		return (0);
	// draw_map(&cub, &cub.img);
	draw_screen(&cub, &cub.img3d);
	mlx_put_image_to_window(cub.mlx3d.mlx, cub.mlx3d.win, cub.img3d.img, 0, 0);
	mlx_hook(cub.mlx3d.win, 17, 0, wclose, &cub);
	mlx_hook(cub.mlx3d.win, 2, 1L << 0, &exec_key, &cub);
	mlx_loop(cub.mlx3d.mlx);
	return (0);
}
