/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:49 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 17:36:43 by aselnet          ###   ########.fr       */
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

int	check_wall(double x, double y, t_cub *cub)
{
	int		x_tile;
	int		y_tile;

	x_tile = (int) x;
	y_tile = (int) y;
	// printf("x is %.2f\n", x);
	// printf("y is %.2f\n", y);
	// printf("x_tile is %d\n", x_tile);
	// printf("y_tile is %d\n", y_tile);
	if (cub->map[x_tile][y_tile] == '1')
		return (1);
	return (0);
}

int	wclose(t_cub *cub)
{
	ft_free_arr(cub->map);
	free(cub->path);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	mlx_destroy_display(cub->mlx.mlx);
	free(cub->mlx.mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
