/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:55:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 16:01:42 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pre_set_rgb(int *color, char *str)
{
	*color = set_rgb(str);
	if (*color < 0)
		return (1);
	return (0);
}

int	set_info(char **buff, t_parsing *data)
{
	if (ft_strcmp(buff[0], "NO") == 0)
	{
		if (set_no(buff, data) != 0)
			return (1);
	}
	else if (ft_strcmp(buff[0], "SO") == 0)
	{
		if (set_so(buff, data) != 0)
			return (1);
	}
	else if (ft_strcmp(buff[0], "EA") == 0)
	{
		if (set_ea(buff, data) != 0)
			return (1);
	}
	else if (ft_strcmp(buff[0], "WE") == 0)
	{
		if (set_we(buff, data) != 0)
			return (1);
	}
	else if (ft_strcmp(buff[0], "C") == 0)
		return (pre_set_rgb(&data->c, buff[1]));
	else if (ft_strcmp(buff[0], "F") == 0)
		return (pre_set_rgb(&data->f, buff[1]));
	else
	{
		printf("\033[31;01mInfos error :\033[00m Invalid ID \"%s\" !\n", buff[0]);
		return (1);
	}
	return (0);
}

int	parse_elem(char *line, t_parsing *data)
{
	char	**buff;

	line[ft_strlen(line) - 1] = 0;
	buff = ft_split(line, ' ');
	if (ft_arr_len(buff) != 2)
	{
		if (ft_arr_len(buff) > 2)
			printf("\033[31;01mInfos error :\033[00m Invalid \"%s\" !\n", buff[2]);
		else
		{
			printf("\033[31;01mInfos error : \033[00m");
			printf("Missing value for \"%s\" !\n", buff[0]);
		}
		return (ft_free_arr(buff), 1);
	}
	if (set_info(buff, data) != 0)
		return (ft_free_arr(buff), 1);
	return (ft_free_arr(buff), 0);
}

int	check_full_elem(t_parsing *data)
{
	if (!data->no)
		return (0);
	if (!data->so)
		return (0);
	if (!data->ea)
		return (0);
	if (!data->we)
		return (0);
	if (data->c == -1)
		return (0);
	if (data->f == -1)
		return (0);
	return (1);
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
	while (line && !check_full_elem(&cub->parsing))
	{
		if (line[0] != '\n')
		{
			if (parse_elem(line, &cub->parsing) != 0)
			{
				while (line)
				{
					free(line);
					line = get_next_line(cub->parsing.fd);
				}
				return (free(line), close(cub->parsing.fd), 1);
			}
		}
		if (check_full_elem(&cub->parsing))
		{
			cub->parsing.lim_line = ft_strdup(line);
			while (line)
			{
				free(line);
				line = get_next_line(cub->parsing.fd);
			}
			return (close(cub->parsing.fd), (0));
		}
		free(line);
		line = get_next_line(cub->parsing.fd);
	}
	//errWIP
	printf("lol\n");
	return (1);
}
