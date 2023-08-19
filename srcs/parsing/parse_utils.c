/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:36:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/19 17:16:20 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_width(t_parsing *data)
{
	char *line;

	data->width = 0;
	data->fd = open(data->file, O_RDONLY, 0666);
	if (data->fd < 0)
		return (1);
	line = get_next_line(data->fd);
	if (!line)
		return (close(data->fd), 1);
	while (line)
	{
		if ((int)ft_strlen(line) > data->width)
			data->width = ft_strlen(line);
		free(line);
		line = get_next_line(data->fd);
	}
	return (close(data->fd), 0);
}

int	count_lines(char *file)
{
	int	fd;
	int	i;
	char	*line;

	fd = open(file, O_RDONLY, 0666);
	if (fd < 0)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}
