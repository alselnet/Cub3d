/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:55:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/19 20:14:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_elem(char *line, t_parsing *data)
{
	(void) data;
	
	char	**buff;

	buff = ft_split(line, ' ');

	int i = 0;
	while (buff[i])
	{
		printf("%s\n", buff[i]);
		i++;
	}
	
	
	if (ft_arr_len(buff) != 2)
	{
		printf("\033[31;01mInfos error :\033[00m WIP !\n");
		return (ft_free_arr(buff), 1);
	}
	return (ft_free_arr(buff), 0);
}

int	parse_infos(t_cub *cub)
{
	char	*line;
	
	cub->parsing.fd = open(cub->path, O_RDONLY, 0666);
	if (cub->parsing.fd < 0)
		return (1);
	line = get_next_line(cub->parsing.fd);
	if (!line)
	{
		printf("\033[31;01mFile error :\033[00m Empty file !\n");
		return (close(cub->parsing.fd), 1);
	}
	while (line)
	{
		if (line[0] != 0)
		{
			if	(parse_elem(line, &cub->parsing) != 0)
				return (free(line), close(cub->parsing.fd), 1);
		}
		free(line);
		return (close(cub->parsing.fd), 0);//WIP
		line = get_next_line(cub->parsing.fd);
	}
	return (close(cub->parsing.fd), 0);
}