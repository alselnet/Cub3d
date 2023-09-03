/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:12:01 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 20:44:58 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub *cub, int x, int y)
{
	cub->res_x = x;
	cub->res_y = y;
	cub->player.pos[0] = 0;
	cub->player.pos[1] = 0;
	cub->mlx3d.mlx = mlx_init();
	cub->mlx3d.win = mlx_new_window(cub->mlx3d.mlx,
			cub->res_x, cub->res_y, "Cub3d");
	cub->img_wall_n.img = 0;
	cub->img_wall_s.img = 0;
	cub->img_wall_e.img = 0;
	cub->img_wall_w.img = 0;
	cub->img3d.img = mlx_new_image(cub->mlx3d.mlx, cub->res_x, cub->res_y);
	cub->img3d.addr = mlx_get_data_addr(cub->img3d.img,
			&cub->img3d.bits_per_pixel, &cub->img3d.line_length,
			&cub->img3d.endian);
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
	return ;
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
			return (free(cub->path));
		}
	}
	close (fd);
}

void	fetch_player_starting_orientation(t_cub *cub)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = floor(cub->player.pos[0]);
	player_tile_y = floor(cub->dimensions[0] - cub->player.pos[1]);
	if (cub->map[player_tile_y][player_tile_x] == 'W')
		cub->player.orientation = PI;
	else if (cub->map[player_tile_y][player_tile_x] == 'N')
		cub->player.orientation = PI * 0.5;
	else if (cub->map[player_tile_y][player_tile_x] == 'E')
		cub->player.orientation = 0;
	else if (cub->map[player_tile_y][player_tile_x] == 'S')
		cub->player.orientation = PI * 1.5;
}

void	fetch_player_start(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (ft_isinbase(cub->map[y][x], "NSEW"))
			{
				cub->player.pos[0] = x;
				cub->player.pos[1] = cub->dimensions[0] - y;
				fetch_player_starting_orientation(cub);
				cub->player.pos[0] += 0.5;
				cub->player.pos[1] -= 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}
