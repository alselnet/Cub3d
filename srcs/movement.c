/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 17:08:55 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	correct_orientation(t_cub *cub)
{
	if (cub->player.orientation < 0)
		cub->player.orientation = 2 * PI;
	else if (cub->player.orientation > 2 * PI)
		cub->player.orientation = 0;
}

void	refresh_img(t_cub *cub)
{
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_map(cub, &cub->img);
	draw_fov(cub, &cub->img);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
}

void	rotate(char dir, t_cub *cub)
{
	if (dir == 'R')
		cub->player.orientation -= ROT_STEP;
	else if (dir == 'L')
		cub->player.orientation += ROT_STEP;
	correct_orientation(cub);
	define_dir(cub);
	refresh_img(cub);
}

void	move(char dir, t_cub *cub)
{
	if (dir =='L')
	{
		cub->player.pos[0] += (MS) * (DELTA * cos(cub->player.orientation - (PI * 0.5)));
		cub->player.pos[1] += (MS) * (DELTA * sin(cub->player.orientation - (PI * 0.5)));
	}
	else if (dir == 'R')
	{
		cub->player.pos[0] += (MS) * (DELTA * cos(cub->player.orientation + (PI * 0.5)));
		cub->player.pos[1] += (MS) * (DELTA * sin(cub->player.orientation + (PI * 0.5)));
	}
	correct_orientation(cub);
	if (dir == 'D')
	{
		cub->player.pos[0] += MS * cub->player.dir[0];
		cub->player.pos[1] += MS * cub->player.dir[1];
	}
	else if (dir == 'U')
	{
		cub->player.pos[0] -= MS * cub->player.dir[0];
		cub->player.pos[1] -= MS * cub->player.dir[1];
	}
	define_dir(cub);
	refresh_img(cub);
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
