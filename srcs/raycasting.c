/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:10:20 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/12 16:33:46 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_hray(t_cub *cub, t_ray *hray, double vector)
{
	hray->ray_len = 10000;
	if (fabs(vector - 0) < 0.0002 || fabs(vector - PI) < 0.0002
		|| fabs(vector - (PI * 2)) < 0.0002)
	{
		hray->ray_x = cub->player.pos[0];
		hray->ray_y = cub->player.pos[1];
		return ;
	}
	else if (vector > PI)
	{
		hray->ray_y = (double)(int)(cub->player.pos[1]) - 0.0001;
		hray->ray_x = ((hray->ray_y - cub->player.pos[1]))
			/ tan(vector) + cub->player.pos[0];
		hray->delta_y = -1;
		hray->delta_x = hray->delta_y / tan(vector);
	}
	else
	{
		hray->ray_y = (double)(int)(cub->player.pos[1]) + 1.0001;
		hray->ray_x = ((hray->ray_y - cub->player.pos[1])
				/ tan(vector)) + cub->player.pos[0];
		hray->delta_y = 1;
		hray->delta_x = hray->delta_y / tan(vector);
	}
}

t_ray	horizontal_check_ray(t_cub *cub, double vector)
{
	t_ray	hray;

	hray.max_view = 0;
	init_ray(&hray);
	set_hray(cub, &hray, vector);
	while (hray.max_view < 1000)
	{
		if (hray.ray_y >= 0.0 && hray.ray_y < cub->dimensions[0]
			&& hray.ray_x >= 0.0 && hray.ray_x < cub->dimensions[1]
			&& cub->map[(int)(cub->dimensions[0]
				- hray.ray_y)][(int)hray.ray_x] == '1')
		{
			hray.ray_len = hyp_len(cub->player.pos[0], hray.ray_x,
					cub->player.pos[1], hray.ray_y);
			return (hray);
		}
		else
		{
			hray.ray_x += hray.delta_x;
			hray.ray_y += hray.delta_y;
			hray.max_view++;
		}
	}
	return (hray);
}

void	set_vray(t_cub *cub, t_ray *vray, double vector)
{
	vray->ray_len = 10000;
	if (fabs(vector - PI * 0.5) < 0.0002
		|| fabs(vector - PI * 1.5) < 0.0002)
	{
		vray->ray_x = cub->player.pos[0];
		vray->ray_y = cub->player.pos[1];
		return ;
	}
	if (vector > PI * 0.5 && vector < PI * 1.5)
	{
		vray->ray_x = (double)(int)(cub->player.pos[0]) - 0.0001;
		vray->ray_y = ((vray->ray_x - cub->player.pos[0])
				* tan(vector)) + cub->player.pos[1];
		vray->delta_x = -1;
		vray->delta_y = vray->delta_x * tan(vector);
	}
	else
	{
		vray->ray_x = (double)(int)(cub->player.pos[0]) + 1.0001;
		vray->ray_y = ((vray->ray_x - cub->player.pos[0])
				* tan(vector)) + cub->player.pos[1];
		vray->delta_x = 1;
		vray->delta_y = vray->delta_x * tan(vector);
	}	
}

t_ray	vertical_check_ray(t_cub *cub, double vector)
{
	t_ray	vray;

	vray.max_view = 0;
	init_ray(&vray);
	set_vray(cub, &vray, vector);
	while (vray.max_view < 1000)
	{
		if (vray.ray_y >= 0.0 && vray.ray_y < cub->dimensions[0]
			&& vray.ray_x >= 0.0 && vray.ray_x < cub->dimensions[1]
			&& cub->map[(int)(cub->dimensions[0]
				- vray.ray_y)][(int)(vray.ray_x)] == '1')
		{
			vray.ray_len = hyp_len(cub->player.pos[0], vray.ray_x,
					cub->player.pos[1], vray.ray_y);
			return (vray);
		}
		else
		{
			vray.ray_x += vray.delta_x;
			vray.ray_y += vray.delta_y;
			vray.max_view++;
		}
	}
	return (vray);
}

t_ray	cast_ray(t_cub *cub, double vector)
{
	t_ray	hray;
	t_ray	vray;

	hray = horizontal_check_ray(cub, vector);
	vray = vertical_check_ray(cub, vector);
	if (hray.ray_len < vray.ray_len)
	{
		if (hray.ray_y > cub->player.pos[1])
			hray.side = 'S';
		else
			hray.side = 'N';
		return (hray);
	}
	else
	{
		if (vray.ray_x > cub->player.pos[0])
			vray.side = 'W';
		else
			vray.side = 'E';
		return (vray);
	}
}
