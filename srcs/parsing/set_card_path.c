/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_card_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:31:59 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 00:12:22 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_no(char **buff, t_parsing *data)
{
	int	fd;
	
	if (data->no)
	{
		printf("\033[31;01mInfos error :\033[00m Multiple NO textures paths !\n");
		return (1);
	}
	data->no = ft_strdup(buff[1]);
	if (!data->no)
		return (ft_free_arr(buff), 1);
	fd = open(data->no, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31;01mInfos error :\033[00m Bad NO texture path !\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	set_so(char **buff, t_parsing *data)
{
	int	fd;

	if (data->so)
	{
		printf("\033[31;01mInfos error :\033[00m Multiple SO textures paths !\n");
		return (1);
	}
	data->so = ft_strdup(buff[1]);
	if (!data->so)
		return (ft_free_arr(buff), 1);
	fd = open(data->so, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31;01mInfos error :\033[00m Bad SO texture path !\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	set_ea(char **buff, t_parsing *data)
{
	int	fd;

	if (data->ea)
	{
		printf("\033[31;01mInfos error :\033[00m Multiple EA textures paths !\n");
		return (1);
	}
	data->ea = ft_strdup(buff[1]);
	if (!data->ea)
		return (ft_free_arr(buff), 1);
	fd = open(data->ea, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31;01mInfos error :\033[00m Bad EA texture path !\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	set_we(char **buff, t_parsing *data)
{
	int	fd;

	if (data->we)
	{
		printf("\033[31;01mInfos error :\033[00m Multiple WE textures paths !\n");
		return (1);
	}
	data->we = ft_strdup(buff[1]);
	if (!data->we)
		return (ft_free_arr(buff), 1);
	fd = open(data->we, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31;01mInfos error :\033[00m Bad WE texture path !\n");
		return (1);
	}
	close(fd);
	return (0);
}
