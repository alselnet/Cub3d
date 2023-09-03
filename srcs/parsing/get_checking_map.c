/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checking_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:42:46 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/03 18:54:35 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Rempli la premiere ligne de la map avec des 'X'
int	fill_top_limit(t_parsing *data)
{
	int	i;

	data->map[0] = malloc(sizeof(char) * (data->width + 2));
	if (!data->map[0])
		return (1);
	i = 0;
	while (i < data->width + 1)
	{
		data->map[0][i] = 'X';
		i++;
	}
	data->map[0][i] = 0;
	return (0);
}

//Copie une ligne du file dans la map en l'entourant de 'X'
void	fill_line(char *map, char *line, t_parsing *data)
{
	int	i;
	int	j;

	map[0] = 'X';
	i = 1;
	j = 0;
	while (line[j] && ft_isspace(line[j]))
	{
		map[i] = 'X';
		i++;
		j++;
	}
	while (line[j] && line[j] != '\n')
	{
		if (ft_isspace(line[j]))
			map[i] = 'X';
		else if (line[j] == 'X')
			map[i] = 'x';
		else
			map[i] = line[j];
		i++;
		j++;
	}
	while (i < data->width + 1)
	{
		map[i] = 'X';
		i++;
	}
	map[i] = 0;
}

//Rempli la derniere ligne de la map avec des 'X'
char	*fill_bot_limit(char *prev)
{
	char	*map;
	int	i;

	map = malloc(sizeof(char) * (ft_strlen(prev) + 1));
	i = 0;
	while (i < (int)ft_strlen(prev))
	{
		map[i] = 'X';
		i++;
	}
	map[i] = 0;
	return (map);
}

//Set la map de verification = map entouree de 'X'
int get_checking_map(t_parsing *data, t_cub *cub)
{
	char	*line;
	int	i;
	// (void) cub;
	
	data->map = ft_calloc(count_lines(data) + 3, sizeof(char *));
	if (!data->map)
		return (1);
	if (go_to_map(data, cub) != 0)
		return (1);//WIP
	line = get_next_line(data->fd);
	if (!line)
		return (close(data->fd), 1);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(data->fd);
	}
	if (fill_top_limit(data) != 0)
		return (close(data->fd), 1);
	i = 1;
	while (line)
	{
		data->map[i] = malloc(sizeof(char) * (data->width + 2));
		fill_line(data->map[i], line, data);
		i++;
		free(line);
		line = get_next_line(data->fd);
	}
	data->map[i] = fill_bot_limit(data->map[i - 1]);
	data->map[i + 1] = 0;
	close(data->fd);
	return (0);
}
