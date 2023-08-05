/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checking_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:42:46 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/05 22:49:19 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Rempli la premiere ligne de la map avec des 'X'
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

//Copie une ligne du file dans la map en l'entourant de 'X'
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

// void	fill_content(char *map, char *line)
// {
// 	map = malloc(sizeof(char) * (ft_strlen(line) + 2));
// 	map[0] = 'X';
// 	fill_line(map, line);
// }

//Set la map de verification = map entouree de 'X'
int get_checking_map(t_parsing *data)
{
	char	*line;
	int	fd;
	int	i;

	data->map = malloc(sizeof(char *) * (count_lines(data->file) + 3));
	if (!data->map)
		return (1);
	fd = open(data->file, O_RDONLY, 0666);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	if (fill_top_limit(data->map, line) != 0)
		return (close(fd), 1);
	i = 1;
	while (line)
	{
		data->map[i] = malloc(sizeof(char) * (ft_strlen(line) + 2));
		fill_line(data->map[i], line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->map[i] = fill_bot_limit(data->map[i - 1]);
	data->map[i + 1] = 0;
	close(fd);
	return (0);
}
