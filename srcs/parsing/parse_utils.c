/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:36:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 14:09:11 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_width(t_parsing *data)
{
	char	*line;

	data->width = 0;
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

int	count_lines(t_parsing *data)
{
	int	i;
	char	*line;

	i = 0;
	line = get_next_line(data->fd);
	if (!line)
		return (0);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(data->fd);
	}
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	return (i);
}

int	go_to_map(t_parsing *data, t_cub *cub)
{
	char	*line;
	
	data->fd = open(cub->path, O_RDONLY, 0666);
	if (data->fd < 0)
		return (1);
	line = get_next_line(data->fd);
	if (!line)
		return (close(data->fd), 1);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		if (ft_strcmp(line, data->lim_line) == 0)
			return (free(line), 0);
		free(line);
		line = get_next_line(data->fd);
	}
	printf("err\n");
	return (1);
}

void	skip_empty_lines(char *line, int fd)
{
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
}
