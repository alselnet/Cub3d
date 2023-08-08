/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checking_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:42:46 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/09 01:22:40 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_width(t_parsing *data)
{
	int	fd;
	char *line;

	data->width = 0;
	fd = open(data->file, O_RDONLY, 0666);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	while (line)
	{
		if ((int)ft_strlen(line) > data->width)
			data->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

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
int get_checking_map(t_parsing *data)
{
	char	*line;
	int	fd;
	int	i;

	get_width(data);
	data->map = malloc(sizeof(char *) * (count_lines(data->file) + 3));
	if (!data->map)
		return (1);
	fd = open(data->file, O_RDONLY, 0666);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	if (fill_top_limit(data) != 0)
		return (close(fd), 1);
	i = 1;
	while (line)
	{
		data->map[i] = malloc(sizeof(char) * (data->width + 2));
		fill_line(data->map[i], line, data);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->map[i] = fill_bot_limit(data->map[i - 1]);
	data->map[i + 1] = 0;
	close(fd);
	return (0);
}
