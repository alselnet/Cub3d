/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/03 00:52:17 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(char dir, t_cub *cub)
{
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	if (dir == 'L')
	{
		if (cub->player.orientation - (PI / 36) < 0)
			cub->player.orientation = (2 * PI) - (PI / 36);
		else
			cub->player.orientation -= PI / 36;
	}
	else if (dir == 'R')
	{
		if (cub->player.orientation + (PI / 36) > 2 * PI)
			cub->player.orientation = PI / 36;
		else
			cub->player.orientation += PI / 36;
	}
	draw_map(cub, &cub->img);
	draw_fov(cub, &cub->img);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
}

void	move(char dir, t_cub *cub)
{
	double	slope;
	double	delta;

	slope = tan(cub->player.orientation);
	delta = 0.01;
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	// if (dir == 'U') DEGUEULASSE MARCHE PAS MERDE
	// {
	// 	if (cub->player.orientation > (PI * 0.5) && cub->player.orientation < PI * 1.5)
	// 		cub->player.pos_x += delta;
	// 	else 
	// 		cub->player.pos_x -= delta;
	// 	if (cub->player.orientation > 0 && cub->player.orientation < PI * 0.5)
	// 		cub->player.pos_y -= (slope * delta);
	// 	else if (cub->player.orientation > PI && cub->player.orientation < PI * 1.5)
	// 		cub->player.pos_y -= (slope * delta);
	// 	else 
	// 		cub->player.pos_y += (slope * delta);
	// }
	// else if (dir == 'D')
	// {
	// 	cub->player.pos_x += cub->player.orientation / 2;
	// 	cub->player.pos_y += cub->player.orientation / 2;
	// }
	draw_map(cub, &cub->img);
	draw_fov(cub, &cub->img);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
}

int	exec_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		wclose(cub);
	else if (keycode == XK_a)
		rotate('L', cub);
	else if (keycode == XK_w)
	 	move('U', cub);
	else if (keycode == XK_d)
		rotate('R', cub);
	// else if (keycode == XK_s)
	//  	move('D', cub);
	return (0);
}
