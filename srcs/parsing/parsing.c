/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/05 22:30:13 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_top_limit(char **map, char *line)
{
	int	i;

	map[0] = malloc(sizeof(char) * (ft_strlen(line) + 2));
	if (!map[0])
		return (1);
	i = 0;
	while (i < (int)ft_strlen(line) + 1)
	{
		map[0][i] = 'X';
		i++;
	}
	map[0][i] = 0;
	return (0);
}

void	fill_line(char *map, char *line)
{
	int	i;
	int	j;

	map[0] = 'X';
	i = 1;
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		map[i] = line[j];
		i++;
		j++;
	}
	map[i] = 'X';
	map[i + 1] = 0;
}

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

int get_map(t_parsing *data)
{
	char	*line;
	int	fd;
	int	i;

	data->map = malloc(sizeof(char *) * (count_lines(data->file) + 3));
	if (!data->map)
		return (1);
	fd = open(data->file, O_RDONLY, 0666);
	if (fd < 0)
		return(1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	if (fill_top_limit(data->map, line) != 0)
		return (close(fd), 1);
	i = 1;
	while (line)
	{
		data->map[i] = malloc(sizeof(char) * (ft_strlen(line) + 2));
		data->map[i][0] = 'X';
		fill_line(data->map[i], line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->map[i] = fill_bot_limit(data->map[i - 1]);
	data->map[i + 1] = 0;
	return (0);
}

void	parsing(char *file)
{
	t_parsing	data;

	data.file = file;
	if (get_map(&data) != 0)
	{
		// free_all
		exit(1);
	}
	int	i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	free(data.map);
}