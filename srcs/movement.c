/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:06:37 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_img(t_cub *cub)
{
	mlx_destroy_image(cub->mlx3d.mlx, cub->img3d.img);
	cub->img3d.img = mlx_new_image(cub->mlx3d.mlx, cub->res_x, cub->res_y);
	cub->img3d.addr = mlx_get_data_addr(cub->img3d.img,
			&cub->img3d.bits_per_pixel, &cub->img3d.line_length,
			&cub->img3d.endian);
	draw_3d(cub, -(FOV / 2));
	mlx_put_image_to_window(cub->mlx3d.mlx,
		cub->mlx3d.win, cub->img3d.img, 0, 0);
}

int	exec_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		wclose(cub);
	else if (keycode == XK_Left)
		rotate('L', cub);
	else if (keycode == XK_Right)
		rotate('R', cub);
	else if (keycode == XK_a)
		strafe('L', cub);
	else if (keycode == XK_d)
		strafe('R', cub);
	else if (keycode == XK_w || keycode == XK_Up)
		move('U', cub);
	else if (keycode == XK_s || keycode == XK_Down)
		move('D', cub);
	return (0);
}
