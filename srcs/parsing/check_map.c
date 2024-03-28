/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:17:46 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 13:53:58 by jthuysba         ###   ########.fr       */
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
		if (check_line_limits(data->map[i], data->map[i - 1],
				data->map[i + 1]) != 0)
		{
			printf("\033[31;01mInvalid map : \033[00m");
			printf("The map has to be closed !\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_line_player(char *map, t_parsing *data)
{
	int	i;

	i = 1;
	while (map[i + 1])
	{
		if (ft_isinbase(map[i], "NSEW") && data->player_flag == 0)
			data->player_flag = 1;
		else if (ft_isinbase(map[i], "NSEW") && data->player_flag == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_map_player(t_parsing *data)
{
	int	i;

	i = 1;
	while (data->map[i])
	{
		if (check_line_player(data->map[i], data) != 0)
		{
			printf("\033[31;01mInvalid map : \033[00m");
			printf("Too many player positions !\n");
			return (1);
		}
		i++;
	}
	if (data->player_flag == 0)
	{
		printf("\033[31;01mInvalid map :\033[00m No player position found !\n");
		return (1);
	}
	return (0);
}

int	check_bad_char(t_parsing *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (!ft_isinbase(data->map[i][j], "01NSEWX"))
			{
				printf("\033[31;01mInvalid map : \033[00m");
				printf("Invalid character found !\n");
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
