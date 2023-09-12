/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:34:52 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 20:01:09 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	launch_file(char **line, t_cub *cub)
{
	cub->parsing.fd = open(cub->path, O_RDONLY, 0666);
	if (cub->parsing.fd < 0)
		return (1);
	*line = get_next_line(cub->parsing.fd);
	if (line && !*line)
	{
		printf("\033[31;01mFile error :\033[00m Empty file !\n");
		return (close(cub->parsing.fd), 1);
	}
	skip_empty_lines(line, cub->parsing.fd);
	return (0);
}
