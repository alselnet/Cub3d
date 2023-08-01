/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/01 19:59:56 by jthuysba         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && y >= 0 && x < 1920 && y < 1080))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, 512, 512, "Cub2d");
	cub->img.img = mlx_new_image(cub->mlx.mlx, 512, 512);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}

char	*fill_line()
{
	int	i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (100 + 1));
	if (!line)
		return (NULL);
	line[i] = '1';
	i++;
	while (i < 100 - 1)
	{
		line[i] = '0';
		i++;
	}
	line[i] = '1';
	i++;
	line[i] = 0;
	return (line);
}

// No parsing
int	init_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map = malloc(sizeof(char *) * (100 + 1));
	if (!cub->map)
		return (1);
	while (i < 100)
	{
		cub->map[i] = fill_line();
		if (!cub->map[i])
			return (free(cub->map), 1);
		i++;
	}
	cub->map[i] = 0;
	return (0);
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
			if (cub->map[y][x] == '0')
				my_mlx_pixel_put(&cub->img, x, y, 0xfff0f6);
			else if (cub->map[y][x] == '1')
				my_mlx_pixel_put(&cub->img, x, y, 0xfa6339);
			x++;
		}
		x = 0;
		y++;
	}
}

int	main()
{
	t_cub	cub;

	init_mlx(&cub);
	if (init_map(&cub) != 0)
		return (1);

	draw_map(&cub);

	mlx_put_image_to_window(cub.mlx.mlx, cub.mlx.win, cub.img.img, 0, 0);

	mlx_hook(cub.mlx.win, 17, 0, wclose, &cub.mlx);
	mlx_hook(cub.mlx.win, 2, 1L << 0, &exec_key, &cub.mlx);
	mlx_loop(cub.mlx.mlx);
	
	ft_free_arr(cub.map);
	return (0);
}
