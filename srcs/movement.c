/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/12 19:58:03 by jthuysba         ###   ########.fr       */
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
	draw_3d(cub, - ((double)FOV / 2.0));
	mlx_put_image_to_window(cub->mlx3d.mlx,
		cub->mlx3d.win, cub->img3d.img, 0, 0);
}

int	check_wall_player(double x, double y, t_cub *cub)
{
	int		x_tile;
	int		y_tile;

	x_tile = (int) x;
	y_tile = (int)(cub->dimensions[0] - y);
	if (x_tile < 0 || x_tile > cub->dimensions[1])
		return (1);
	else if (y_tile < 0 || y_tile > cub->dimensions[0])
		return (1);
	if (cub->map[y_tile][x_tile] == '1')
		return (1);
	return (0);
}

int	check_wall(double x, double y, t_cub *cub)
{
	if (check_wall_player(x, y, cub) == 1)
		return (1);
	else if (check_wall_player(x, y + PADDING, cub) == 1)
		return (1);
	else if (check_wall_player(x + PADDING, y, cub) == 1)
		return (1);
	else if (check_wall_player(x, y - PADDING, cub) == 1)
		return (1);
	else if (check_wall_player(x - PADDING, y, cub) == 1)
		return (1);
	return (0);
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
