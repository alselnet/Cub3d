/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/04 19:28:21 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(char dir, t_cub *cub)
{
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	if (dir == 'R')
	{
		if (cub->player.orientation - (PI / 36) < 0)
			cub->player.orientation = (2 * PI) - (PI / 36);
		else
			cub->player.orientation -= PI / 36;
	}
	else if (dir == 'L')
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
	double	delta;
	double	vector;

	delta = -0.1;
	vector = cub->player.orientation;
	if (dir == 'D')
		delta = -delta;
	else if (dir =='L')
		vector += PI *0.5;
	else if (dir == 'R')
		vector -= PI *0.5;
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	printf("pos_x is %f\n", cub->player.pos_x);
	printf("pos_y is %f\n", cub->player.pos_y);
	printf("orientation is %f * PI\n", cub->player.orientation / PI);
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	cub->player.pos_y += delta * sin(vector);
	cub->player.pos_x += delta * cos(vector);
	draw_map(cub, &cub->img);
	draw_fov(cub, &cub->img);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
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
		move('L', cub);
	else if (keycode == XK_d)
		move('R', cub);
	else if (keycode == XK_w || keycode == XK_Up)
	 	move('U', cub);
	else if (keycode == XK_s || keycode == XK_Down)
	 	move('D', cub);
	return (0);
}
