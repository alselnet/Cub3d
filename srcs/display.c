/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:00 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/01 23:11:40 by aselnet          ###   ########.fr       */
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

void	draw_tile(t_img *img, int x, int y, int color)
{
	int	a;
	int	b;

	b = y*30;
	while (b < (y + 1) * 30)
	{
		a = x*30;
		while (a < (x + 1) * 30)
		{
			my_mlx_pixel_put(img, a, b, color);
			a++;
		}
		b++;
	}
}
void	draw_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < ft_arr_len(cub->map))
	{
		while (x < (int)ft_strlen(cub->map[y]))
		{
			if (ft_isinbase(cub->map[y][x], "0NSEW"))
				draw_tile(&cub->img, x, y, 0xfff0f6);
			else if (cub->map[y][x] == '1')
				draw_tile(&cub->img, x, y, 0xfa6339);
			x++;
		}
		x = 0;
		y++;
	}
}