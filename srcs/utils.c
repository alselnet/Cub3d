/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:49 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/15 03:14:34 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	// printf("x is %.2f\n", x);
	// printf("y is %.2f\n", y);
	// printf("x_tile is %d\n", x_tile);
	// printf("y_tile is %d\n", y_tile);
	if (cub->map[y_tile][x_tile] == '1')
		return (1);
	return (0);
}

int	wclose(t_cub *cub)
{
	ft_free_arr(cub->map);
	free(cub->path);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	mlx_destroy_window(cub->mlx3d.mlx, cub->mlx3d.win);
	mlx_destroy_display(cub->mlx.mlx);
	mlx_destroy_display(cub->mlx3d.mlx);
	free(cub->mlx.mlx);
	free(cub->mlx3d.mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
