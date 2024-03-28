/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:08:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/03 19:16:02 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_parsing(t_parsing *data)
{
	if (data->lim_line)
		free(data->lim_line);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
}

void	destroy_all(t_cub *cub)
{
	if (cub->path)
		free(cub->path);
	if (cub->map)
		ft_free_arr(cub->map);
	free_parsing(&cub->parsing);
}
