/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:14:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 14:17:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(t_cub *cub)
{
	int	size;
	int	fd;

	size = ft_strlen(cub->path);
	fd = open(cub->path, O_RDONLY, 0666);
	if (fd < 0)
	{
		printf("\033[31;01mInvalid file :\033[00m File not found !\n");
		return (1);
	}
	if (ft_strcmp(cub->path + (size - 4), ".cub") != 0)
	{
		printf("\033[31;01mInvalid file :\033[00m Not a .cub file !\n");
		return (close(fd), 1);
	}
	close(fd);
	return (0);
}

int	parse_args(int argc, char **argv, t_cub *cub)
{
	if (argc > 2)
	{
		printf("\033[31;01mArgs error :\033[00m Too many arguments !\n");
		return (1);
	}
	else if (argc <= 1)
	{
		printf("\033[31;01mArgs error :\033[00m Not enough arguments !\n");
		return (1);
	}
	if (ft_isinbase('/', argv[1]) == 0)
		cub->path = ft_strjoin("maps/", argv[1]);
	else
		cub->path = ft_strdup(argv[1]);
	if (check_file(cub) != 0)
		return (free(cub->path), 1);
	return (0);
}
