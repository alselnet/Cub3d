/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:18:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/07 17:36:41 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(char dir, t_cub *cub)
{
	if (dir == 'R')
		cub->player.orientation -= ROT_STEP;
	else if (dir == 'L')
		cub->player.orientation += ROT_STEP;
	correct_orientation(cub);
	define_dir(cub);
	refresh_img(cub);
}

int	check_strafe(char dir, t_cub *cub)
{
	double new_pos[2];

	new_pos[0] = cub->player.pos[0];
	new_pos[1] = cub->player.pos[1];
	if (dir =='L')
	{
		new_pos[0] += MS *
			(DELTA * cos(cub->player.orientation - (PI * 0.5)));
		new_pos[1] += MS *
			(DELTA * sin(cub->player.orientation - (PI * 0.5)));
	}
	else if (dir == 'R')
	{
		new_pos[0] += MS *
			(DELTA * cos(cub->player.orientation + (PI * 0.5)));
		new_pos[1] += MS *
			(DELTA * sin(cub->player.orientation + (PI * 0.5)));
	}
	if (check_wall(new_pos[0], new_pos[1], cub))
		return (1);
	return (0);
}

void	strafe(char dir, t_cub *cub)
{
	if (check_strafe(dir, cub))
		return ;
	if (dir =='L')
	{
		cub->player.pos[0] += MS *
			(DELTA * cos(cub->player.orientation - (PI * 0.5)));
		cub->player.pos[1] += MS *
			(DELTA * sin(cub->player.orientation - (PI * 0.5)));
	}
	else if (dir == 'R')
	{
		cub->player.pos[0] += MS *
			(DELTA * cos(cub->player.orientation + (PI * 0.5)));
		cub->player.pos[1] += MS *
			(DELTA * sin(cub->player.orientation + (PI * 0.5)));
	}
	correct_orientation(cub);
	refresh_img(cub);
}

int	check_move(char dir, t_cub *cub)
{
	double new_pos[2];

	new_pos[0] = cub->player.pos[0];
	new_pos[1] = cub->player.pos[1];
	if (dir == 'D')
	{
		new_pos[0] += MS * cub->player.dir[0];
		new_pos[1] += MS * cub->player.dir[1];
	}
	else if (dir == 'U')
	{
		new_pos[0] -= MS * cub->player.dir[0];
		new_pos[1] -= MS * cub->player.dir[1];
	}
	if (check_wall(new_pos[0], new_pos[1], cub))
		return (1);
	return (0);
}

void	move(char dir, t_cub *cub)
{
	if (check_move(dir, cub))
		return ;
	if (dir == 'D')
	{
		cub->player.pos[0] += MS * cub->player.dir[0];
		cub->player.pos[1] += MS * cub->player.dir[1];
	}
	else if (dir == 'U')
	{
		cub->player.pos[0] -= MS * cub->player.dir[0];
		cub->player.pos[1] -= MS * cub->player.dir[1];
	}
	define_dir(cub);
	refresh_img(cub);
}
