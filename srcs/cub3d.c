/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/01 17:55:04 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wclose(t_mlx *mlx)
{
	//mem_flush(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	exec_key(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		wclose(mlx);
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

int	main()
{
	t_cub	cub;

	cub.mlx.mlx = mlx_init();
	cub.mlx.win = mlx_new_window(cub.mlx.mlx, 512, 512, "Cub2d");
	mlx_hook(cub.mlx.win, 17, 0, wclose, &cub.mlx);
	mlx_hook(cub.mlx.win, 2, 1L << 0, &exec_key, &cub.mlx);
	mlx_loop(cub.mlx.mlx);
	return (0);
}
