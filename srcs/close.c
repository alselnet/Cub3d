/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:31:09 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:36:20 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
