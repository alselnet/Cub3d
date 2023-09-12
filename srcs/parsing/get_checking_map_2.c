/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checking_map_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:12:01 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 14:13:13 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_char(char line, char *map)
{
	if (ft_isspace(line))
		*map = 'X';
	else if (line == 'X')
		*map = 'x';
	else
		*map = line;
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
		set_char(line[j], &map[i]);
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
	int		i;

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
