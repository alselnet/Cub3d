/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:55:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/22 18:16:59 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_elem(char *line, t_parsing *data)
{
	(void) data;
	char	**buff;

	line[ft_strlen(line) - 1] = 0;
	buff = ft_split(line, ' ');
	if (ft_arr_len(buff) != 2)
	{
		printf("\033[31;01mInfos error :\033[00m WIP !\n");
		return (ft_free_arr(buff), 1);
	}
	if (ft_strcmp(buff[0], "NO") == 0)
	{
		if (data->no)
		{
			printf("\033[31;01mInfos error :\033[00m Multiple NO textures paths !\n");
			return (1);
		}
		data->no = ft_strdup(buff[0]);
		if (!data->no)
			return (ft_free_arr(buff), 1);
	}
	else if (ft_strcmp(buff[0], "SO") == 0)
	{
		if (data->so)
		{
			printf("\033[31;01mInfos error :\033[00m Multiple SO textures paths !\n");
			return (1);
		}
		data->so = ft_strdup(buff[0]);
		if (!data->so)
			return (ft_free_arr(buff), 1);
	}
	else if (ft_strcmp(buff[0], "EA") == 0)
	{
		if (data->ea)
		{
			printf("\033[31;01mInfos error :\033[00m Multiple EA textures paths !\n");
			return (1);
		}
		data->ea = ft_strdup(buff[0]);
		if (!data->ea)
			return (ft_free_arr(buff), 1);
	}
	else if (ft_strcmp(buff[0], "WE") == 0)
	{
		if (data->we)
		{
			printf("\033[31;01mInfos error :\033[00m Multiple WE textures paths !\n");
			return (1);
		}
		data->we = ft_strdup(buff[0]);
		if (!data->we)
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
		if (line[0] != '\n')
		{
			if	(parse_elem(line, &cub->parsing) != 0)
			{
				//free struct
				return (free(line), close(cub->parsing.fd), 1);
			}
		}
		free(line);
		// return (close(cub->parsing.fd), 0);//WIP
		line = get_next_line(cub->parsing.fd);
	}
	return (close(cub->parsing.fd), 0);
}