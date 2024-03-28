/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:25:11 by aselnet           #+#    #+#             */
/*   Updated: 2023/09/11 18:36:41 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->side = 0;
	ray->wall_h = 0;
	ray->ray_x = 0;
	ray->ray_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->ray_len = 0;
	ray->max_view = 0;
	return ;
}
