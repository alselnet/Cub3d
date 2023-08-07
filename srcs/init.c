/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:01 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 16:06:04 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub *cub, int x, int y)
{
	cub->res_x = x;
	cub->res_y = y;
	cub->player.pos[0] = 0;
	cub->player.pos[1] = 0;
	cub->player.dir[0] = 0;
	cub->player.dir[1] = 0;
	cub->player.plane[0] = 0;
	cub->player.plane[1] = 0.8;
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->res_x, cub->res_y, "Cub2d");
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->res_x, cub->res_y);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}


void	get_map_size(t_cub *cub)
{
	int		fd;
	char	*line;

	cub->dimensions[0] = 0;
	fd = open(cub->path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (free(cub->path));
	cub->dimensions[1] = ft_strlen(line);
	while (line && *line)
	{
		free (line);
		line = get_next_line(fd);
		cub->dimensions[0]++;
	}	
	free(line);
	close(fd);
	return;
}

void	fetch_map(t_cub *cub)
{
	int		fd;
	int		i;

	i = -1;
	get_map_size(cub);
	cub->map = ft_calloc((cub->dimensions[0]) + 1, sizeof(char *));
	if (!cub->map)
		return (free(cub->path));
	fd = open(cub->path, O_RDONLY);
	while (++i < cub->dimensions[0])
	{
		cub->map[i] = get_next_line(fd);
		if (!cub->map[i])
		{
			close(fd);
			return(free(cub->path));
		}
	}
	close (fd);
}
