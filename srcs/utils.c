/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:49 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:21:18 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	hyp_len(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	correct_orientation(t_cub *cub)
{
	if (cub->player.orientation < 0)
		cub->player.orientation += 2 * PI;
	else if (cub->player.orientation > 2 * PI)
		cub->player.orientation -= 2 * PI;
}

int	check_wall_player(double x, double y, t_cub *cub)
{
	int		x_tile;
	int		y_tile;

	x_tile = (int) x;
	y_tile = (int) cub->dimensions[0] - y;
	if (cub->map[y_tile][x_tile] == '1')
		return (1);
	return (0);
}

int	wclose(t_cub *cub)
{
	ft_free_arr(cub->map);
	free(cub->path);
	mlx_destroy_image(cub->mlx3d.mlx, cub->img3d.img);
	mlx_destroy_image(cub->mlx3d.mlx, cub->img_wall_n.img);
	mlx_destroy_image(cub->mlx3d.mlx, cub->img_wall_s.img);
	mlx_destroy_image(cub->mlx3d.mlx, cub->img_wall_e.img);
	mlx_destroy_image(cub->mlx3d.mlx, cub->img_wall_w.img);
	mlx_destroy_window(cub->mlx3d.mlx, cub->mlx3d.win);
	mlx_destroy_display(cub->mlx3d.mlx);
	free(cub->mlx3d.mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
