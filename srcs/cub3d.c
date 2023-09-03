/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 16:26:16 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"	

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (0);
	cub.path = ft_strjoin("maps/", argv[1]);
	if (!cub.path)
		return (0);
	init_mlx(&cub, 1152, 870);
	load_textures(&cub);
	fetch_map(&cub);
	if (!cub.map)
		return (0);
	// draw_map(&cub, &cub.img);
	draw_screen(&cub, &cub.img3d);
	mlx_put_image_to_window(cub.mlx3d.mlx, cub.mlx3d.win, cub.img3d.img, 0, 0);
	mlx_hook(cub.mlx3d.win, 17, 0, wclose, &cub);
	mlx_hook(cub.mlx3d.win, 2, 1L << 0, &exec_key, &cub);
	mlx_loop(cub.mlx3d.mlx);
	return (0);
}
