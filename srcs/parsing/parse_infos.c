/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:55:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 19:15:07 by jthuysba         ###   ########.fr       */
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
		return (set_no(buff, data));
	else if (ft_strcmp(buff[0], "SO") == 0)
		return (set_so(buff, data));
	else if (ft_strcmp(buff[0], "EA") == 0)
		return (set_ea(buff, data));
	else if (ft_strcmp(buff[0], "WE") == 0)
		return (set_we(buff, data));
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
	buff = ft_split_spaces(line);
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

int	parse_infos(t_cub *cub)
{
	char	*line;

	line = 0;
	if (launch_file(&line, cub) != 0)
		return (1);
	while (line && !check_full_elem(&cub->parsing))
	{
		if (line[0] != '\n')
		{	
			if (parse_elem(line, &cub->parsing) != 0)
			{
				skip_file(line, cub->parsing.fd);
				return (close(cub->parsing.fd), 1);
			}
		}
		if (check_full_elem(&cub->parsing))
		{
			cub->parsing.lim_line = ft_strdup(line);
			skip_file(line, cub->parsing.fd);
			return (close(cub->parsing.fd), (0));
		}
		free(line);
		line = get_next_line(cub->parsing.fd);
	}
	printf("\033[31;01mInfos error :\033[00m Missing infos !\n");
	return (close(cub->parsing.fd), 1);
}
