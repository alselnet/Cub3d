/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 14:16:30 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup_sub(char *str, char to_find, char sub)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == to_find)
			res[i] = sub;
		else
			res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**set_cub_map(t_parsing *data)
{
	char	**cub_map;
	int		i;

	cub_map = malloc(sizeof(char *) * (ft_arr_len(data->map) + 1));
	if (!cub_map)
		return (NULL);
	i = 0;
	while (data->map[i])
	{
		cub_map[i] = ft_strdup_sub(data->map[i], 'X', '1');
		if (!cub_map[i])
			return (NULL);
		i++;
	}
	cub_map[i] = 0;
	return (cub_map);
}

//debug
void	print_map(char *name, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\n\033[35;01m>>>%s<<<\033[00m\n", name);
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'X')
				printf("[\033[30;01m%c\033[00m]", map[i][j]);
			else if (ft_isinbase(map[i][j], "NSEW"))
				printf("[\033[32;01m%c\033[00m]", map[i][j]);
			else if (map[i][j] == '1')
				printf("[\033[34;01m%c\033[00m]", map[i][j]);
			else if (map[i][j] == '0')
				printf("[\033[33;01m%c\033[00m]", map[i][j]);
			else
				printf("[\033[31;01m%c\033[00m]", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	printf("\n");
}

int	map_parsing(t_cub *cub)
{
	cub->parsing.file = cub->path;
	get_width(&cub->parsing);
	if (go_to_map(&cub->parsing, cub) != 0)
		return (1);//WIP
	if (get_checking_map(&cub->parsing, cub) != 0)
		return (ft_free_arr(cub->parsing.map), 1);
	if (check_map_limits(&cub->parsing) != 0)
		return (ft_free_arr(cub->parsing.map), 1);
	if (check_bad_char(&cub->parsing) != 0)
		return (ft_free_arr(cub->parsing.map), 1);
	if (check_map_player(&cub->parsing) != 0)
		return (ft_free_arr(cub->parsing.map), 1);
	printf("\033[32;01mGood !\033[00m\n");
	cub->map = set_cub_map(&cub->parsing);
	return (ft_free_arr(cub->parsing.map), 0);
}
