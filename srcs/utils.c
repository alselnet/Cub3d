/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:49 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/01 23:13:00 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	exec_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		wclose(cub);
/* 	else if (keycode == XK_w)
		move(1, mlx);
	else if (keycode == XK_a)
		move(2, mlx);
	else if (keycode == XK_s)
		move(3, mlx);
	else if (keycode == XK_d)
		move(4, mlx); */
	return (0);
}