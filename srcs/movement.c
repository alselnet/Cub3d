/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/02 17:28:35 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exec_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		wclose(cub);
	/* else if (keycode == XK_w)
		move(1, mlx);
	else if (keycode == XK_a)
		move(2, mlx);
	else if (keycode == XK_s)
		move(3, mlx);
	else if (keycode == XK_d)
		move(4, mlx); */
	return (0);
}
