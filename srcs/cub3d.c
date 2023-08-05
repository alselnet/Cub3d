/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/05 22:58:52 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (0);
	if (ft_isinbase('/', argv[1]) == 0)
		cub.path = ft_strjoin("maps/", argv[1]);
	else
		cub.path = ft_strdup(argv[1]);
	if (map_parsing(cub.path) != 0)
		return (free(cub.path), 1);
	// if (!cub.path)
	// 	return (0);
	// init_mlx(&cub, 1152, 870);
	// fetch_map(&cub);
	// if (!cub.map)
	// 	return (0);
	// draw_map(&cub, &cub.img);
	// draw_player_start(&cub, &cub.img);
	// mlx_put_image_to_window(cub.mlx.mlx, cub.mlx.win, cub.img.img, 0, 0);
	// mlx_hook(cub.mlx.win, 17, 0, wclose, &cub);
	// mlx_hook(cub.mlx.win, 2, 1L << 0, &exec_key, &cub);
	// mlx_loop(cub.mlx.mlx);
	
	free(cub.path);//est cense ne jamais arriver la
	return (0);
}
