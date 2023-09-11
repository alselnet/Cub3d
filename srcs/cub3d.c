/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/12 00:13:39 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"	

void	init_parsing(t_parsing *data)
{
	data->file = 0;
	data->fd = 0;
	data->no = 0;
	data->so = 0;
	data->ea = 0;
	data->we = 0;
	data->c = -1;
	data->f = -1;
	data->lim_line = 0;
	data->width = 0;
	data->map = 0;
	data->player_flag = 0;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void) argc;
	(void) argv;
	ft_memset(&cub, 0, sizeof(t_cub));
	init_parsing(&cub.parsing);
	if (parse_args(argc, argv, &cub) != 0)
		return (destroy_all(&cub), 1);
	if (parse_infos(&cub))
		return (destroy_all(&cub), 1);
	if (go_to_map(&cub.parsing, &cub) != 0)
		return (destroy_all(&cub), 1);
	if (map_parsing(&cub) != 0)
		return (destroy_all(&cub), 1);
	if (!cub.path)
		return (0);
	init_mlx(&cub, 1152, 870);
	draw_screen(&cub, &cub.img3d);
	mlx_put_image_to_window(cub.mlx3d.mlx, cub.mlx3d.win, cub.img3d.img, 0, 0);
	mlx_hook(cub.mlx3d.win, 17, 0, wclose, &cub);
	mlx_hook(cub.mlx3d.win, 2, 1L << 0, &exec_key, &cub);
	mlx_loop(cub.mlx3d.mlx);
	return (0);
}
