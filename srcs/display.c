/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/03 15:31:54 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && y >= 0 && x < 1152 && y < 870))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_img *img, int y, int x, int color)
{
	int	a;
	int	b;

	a = y * 50;
	while (a < (y + 1) * 50)
	{
		b = x * 50;
		while (b < (x + 1) * 50)
		{
			my_mlx_pixel_put(img, b, a, color);
			b++;
		}
		a++;
	}
}

void	draw_map(t_cub *cub, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_arr_len(cub->map))
	{
		j = 0;
		while (j < (int)ft_strlen(cub->map[i]))
		{
			if (ft_isinbase(cub->map[i][j], "0NSEW"))
				draw_tile(img, i, j, 0xfff0f6);
			else if (cub->map[i][j] == '1')
				draw_tile(img, i, j, 0xfa6339);
			j++;
		}
		i++;
	}
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
