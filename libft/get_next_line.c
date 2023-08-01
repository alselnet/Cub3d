/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:05:20 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/23 14:15:22 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fetch_line(int fd, char *line, char *newline)
{
	int		tracker;
	char	*buffer;

	tracker = 1;
	buffer = (char *) ft_calloc (sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	line = (char *) ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return (0);
	line = ft_strjoin_gnl(line, newline);
	while (tracker > 0 && !ft_chr_is_in_base(line, '\n'))
	{
		tracker = read (fd, buffer, BUFFER_SIZE);
		if (tracker >= 0)
			buffer[tracker] = 0;
		line = ft_strjoin(line, buffer);
	}
	free (buffer);
	if (tracker < 0)
	{
		free (line);
		return (0);
	}
	return (line);
}

char	*make_newline(char *line, char *newline)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i] && newline)
		ft_bzero(newline, ft_strlen(newline));
	else if (line[i] == '\n')
		i++;
	while (line[i])
	{
		newline[j] = line[i];
		line[i] = 0;
		i++;
		j++;
	}
	newline[j] = 0;
	return (newline);
}

char	*reset_arr(char *arr)
{
	free(arr);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*newline;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	line = 0;
	if (!newline)
	{
		newline = (char *) ft_calloc (sizeof(char), BUFFER_SIZE);
		if (!newline)
			return (0);
	}
	line = fetch_line(fd, line, newline);
	if (!line || !*line)
	{
		free(line);
		newline = reset_arr(newline);
		return (0);
	}
	if (ft_chr_is_in_base(line, '\n'))
		newline = make_newline(line, newline);
	else if (newline)
		newline = reset_arr(newline);
	return (line);
}
