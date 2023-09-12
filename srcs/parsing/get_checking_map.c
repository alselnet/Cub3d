/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checking_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:42:46 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 17:06:08 by jthuysba         ###   ########.fr       */
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

void	fill_map(char *line, t_parsing *data)
{
	int	i;

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
}

//Set la map de verification = map entouree de 'X'
int	get_checking_map(t_parsing *data, t_cub *cub)
{
	char	*line;
	int		c;

	c = count_lines(data);
	if (c < 0)
	{
		printf("\033[31;01mInvalid map :\033[00m No map !\n");
		return (close(data->fd), 1);
	}
	data->map = ft_calloc(c + 3, sizeof(char *));
	if (!data->map)
		return (close(data->fd), 1);
	if (go_to_map(data, cub) != 0)
		return (close(data->fd), 1);
	line = get_next_line(data->fd);
	if (!line)
		return (close(data->fd), 1);
	skip_empty_lines(line, data->fd);
	if (fill_top_limit(data) != 0)
		return (close(data->fd), 1);
	fill_map(line, data);
	close(data->fd);
	return (0);
}
