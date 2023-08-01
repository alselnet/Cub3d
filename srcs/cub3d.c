/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:40:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/01 22:22:15 by aselnet          ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && y >= 0 && x < 1152 && y < 870))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_cub *cub, int x, int y)
{
	cub->res_x = x;
	cub->res_y = y;
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
			if (cub->map[y][x] == '0')
				draw_tile(&cub->img, x, y, 0xfff0f6);
			else if (cub->map[y][x] == '1')
				draw_tile(&cub->img, x, y, 0xfa6339);
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (0);
	cub.path = ft_strjoin("maps/", argv[1]);
	if (!cub.path)
		return (0);
	init_mlx(&cub, 1152, 870);
	fetch_map(&cub);
	if (!cub.map)
		return (0);
	draw_map(&cub);
	mlx_put_image_to_window(cub.mlx.mlx, cub.mlx.win, cub.img.img, 0, 0);
	mlx_hook(cub.mlx.win, 17, 0, wclose, &cub);
	mlx_hook(cub.mlx.win, 2, 1L << 0, &exec_key, &cub);
	mlx_loop(cub.mlx.mlx);
	
	return (0);
}
