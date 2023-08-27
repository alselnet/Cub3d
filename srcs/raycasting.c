/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:10:20 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/18 19:27:19 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	hyp_len(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_ray	horizontal_check_ray(t_cub *cub, double vector)
{
	t_ray	hray;

	hray.ray_len = 10000;
	hray.max_view = 0;
	if (fabs(vector - 0) < 0.0002 || fabs(vector - PI) < 0.0002|| fabs(vector - (PI * 2)) < 0.0002) // horizontal straight line
	{
		hray.ray_x = cub->player.pos[0];
		hray.ray_y = cub->player.pos[1];
		return (hray);
	}
	else if (vector > PI)
	{
		hray.ray_y = (double)(int)(cub->player.pos[1]) - 0.0001;
		hray.ray_x = ((hray.ray_y - cub->player.pos[1]))/ tan(vector) + cub->player.pos[0];
		hray.delta_y = -1;
		hray.delta_x = hray.delta_y / tan(vector);
	}
	else if (vector < PI)
	{
		hray.ray_y = (double)(int)(cub->player.pos[1]) + 1.0001;
		hray.ray_x = ((hray.ray_y - cub->player.pos[1])/ tan(vector)) + cub->player.pos[0];
		hray.delta_y = 1;
		hray.delta_x = hray.delta_y / tan(vector);
	}
	while (hray.max_view < 1000)
	{
		if (hray.ray_y > -0.001 && hray.ray_y < cub->dimensions[0] && hray.ray_x > -0.001 && hray.ray_x < cub->dimensions[1] && cub->map[(int)(cub->dimensions[0] - hray.ray_y)][(int)hray.ray_x] == '1')
		{
			hray.ray_len = hyp_len(cub->player.pos[0], hray.ray_x, cub->player.pos[1], hray.ray_y);
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

t_ray	vertical_check_ray(t_cub *cub, double vector)
{
	t_ray	vray;

	vray.ray_len = 10000;
	vray.max_view = 0;
	if (fabs(vector - PI * 0.5) < 0.0002 || fabs(vector - PI * 1.5) < 0.0002) // vertical straight line
	{
		vray.ray_x = cub->player.pos[0];
		vray.ray_y = cub->player.pos[1];
		return (vray);
	}
	if (vector > PI * 0.5 && vector < PI * 1.5)
	{
		vray.ray_x = (double)(int)(cub->player.pos[0]) - 0.0001;
		vray.ray_y = ((vray.ray_x - cub->player.pos[0]) * tan(vector)) + cub->player.pos[1];
		vray.delta_x = -1;
		vray.delta_y = vray.delta_x * tan(vector);
	}
	else if (vector < PI * 0.5 || vector > PI * 1.5)
	{
		vray.ray_x = (double)(int)(cub->player.pos[0]) + 1.0001;
		// printf("vray.ray_x is in %f\n", vray.ray_x);
		// printf("cub->player.pos[0] is %f\n", cub->player.pos[0]);
		// printf("tan(vector) is %f\n", tan(vector));
		// printf("(vray.ray_x - cub->player.pos[0]) * tan(vector) is %f\n", (vray.ray_x - cub->player.pos[0]) * tan(vector));
		vray.ray_y = ((vray.ray_x - cub->player.pos[0]) * tan(vector)) + cub->player.pos[1];
		// printf("vray.ray_y is in %f\n", vray.ray_y);
		vray.delta_x = 1;
		vray.delta_y = vray.delta_x * tan(vector);
	}
	while (vray.max_view < 1000)
	{
		// printf("vray_x is %f \n", vray.ray_x);
		// printf("vray_y is %f \n", vray.ray_y);
		// printf("(int)(cub->dimensions[0] - vray.ray_y)is %d\n", (int)(cub->dimensions[0] - vray.ray_y));
		if (vray.ray_y > 0 && vray.ray_y < cub->dimensions[0] && vray.ray_x > 0 && vray.ray_x < cub->dimensions[1] && cub->map[(int)(cub->dimensions[0] - vray.ray_y)][(int)(vray.ray_x)] == '1')
		{
			vray.ray_len = hyp_len(cub->player.pos[0], vray.ray_x, cub->player.pos[1], vray.ray_y);
			// printf("vray hit in {%f;%f} \n", vray.ray_x, vray.ray_y);
			// printf("vray len is : %f \n", vray.ray_len);
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
	t_ray	ray;

	// printf("-------------------\n");
	// printf("player pos is {%f;%f} \n", cub->player.pos[0], cub->player.pos[1]);
	// printf("vector is %f * PI\n", cub->player.orientation/ PI);
	// printf("cub->dimensions[0] is %d\n", cub->dimensions[0]);
	// printf("cub->dimensions[1] is %d\n", cub->dimensions[1]);
	hray = horizontal_check_ray(cub, vector);
	vray = vertical_check_ray(cub, vector);
	// if (fabs(vector - (PI * 0.5)) < 0.09 || fabs(vector - (PI * 1.5)) < 0.09)
	// {
	// 	printf("vray len was : %f \n", vray.ray_len);
	// 	return (hray);
	// }
	if (hray.ray_len < vray.ray_len)
	{
		ray = hray;
		if (ray.ray_y > cub->player.pos[1])
			ray.side = 'S';
		else
			ray.side = 'N';
	}
	else
	{
		ray = vray;
		if (ray.ray_x > cub->player.pos[0])
			ray.side = 'W';
		else
			ray.side = 'E';
	}
	return (ray);
}