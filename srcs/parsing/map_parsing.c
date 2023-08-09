/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/09 17:40:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_limits(char *line, char *prev, char *next)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isinbase(line[i], "NSEW0"))
		{
			if ((line[i - 1] && line[i - 1] == 'X')
				|| (line[i + 1] && line[i + 1] == 'X'))
				return (1);
			if ((prev[i] && prev[i] == 'X') || (next[i] && next[i] == 'X'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_map_limits(t_parsing *data)
{
	int	i;

	i = 1;
	while (data->map[i + 1])
	{
		if (check_line_limits(data->map[i], data->map[i - 1], data->map[i + 1]) != 0)
		{
			printf("\033[31;01mInvalid map :\033[00m The map has to be closed !\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// int	check_line_player(char *line, t_parsing *data)
// {
// 	int	i;

// 	i = 1;
// 	while (line[i + 1])
// 	{
// 		if ()
// 		{

// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	check_map_player(t_parsing *data)
// {
// 	int	i;

// 	i = 1;
// 	while (data->map[i])
// 	{
// 		check_line_player(data->map[i], data);
// 		i++;
// 	}
// 	return (0);
// }

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
	// if (check_map_player(&data) != 0)
	// 	return (ft_free_arr(data.map), 1);
	printf("\033[32;01mGood !\033[00m\n");
	return (ft_free_arr(data.map), 0);
}