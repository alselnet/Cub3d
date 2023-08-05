/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/05 23:17:35 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char *line, char *prev, char *next)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
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

int	check_map(char **map)
{
	int	i;

	i = 1;
	while (map[i + 1])
	{
		if (check_line(map[i], map[i - 1], map[i + 1]) != 0)
		{
			printf("Error: The map has to be closed !\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	map_parsing(char *file)
{
	t_parsing	data;

	data.file = file;
	if (get_checking_map(&data) != 0)
		return (ft_free_arr(data.map), 1);
	// int i = 0;
	// while (data.map[i])
	// {
	// 	printf("%s\n", data.map[i]);
	// 	i++;
	// }
	if (check_map(data.map) != 0)
		return (1);
	return (ft_free_arr(data.map), 0);
}