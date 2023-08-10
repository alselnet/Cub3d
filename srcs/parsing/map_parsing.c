/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/10 17:18:13 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_parsing(char *file)
{
	t_parsing	data;

	data.file = file;
	data.player_flag = 0;
	get_width(&data);
	if (get_checking_map(&data) != 0)
		return (ft_free_arr(data.map), 1);
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	if (check_map_limits(&data) != 0)
		return (ft_free_arr(data.map), 1);
	if (check_bad_char(&data) != 0)
		return (ft_free_arr(data.map), 1);
	if (check_map_player(&data) != 0)
		return (ft_free_arr(data.map), 1);
	printf("\033[32;01mGood !\033[00m\n");
	return (ft_free_arr(data.map), 0);
}