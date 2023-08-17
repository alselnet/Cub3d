/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:49:21 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/17 19:35:32 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup_sub(char *str, char to_find, char sub)
{
	char	*res;
	int	i;

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
	printf("%c\n", res[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**set_cub_map(t_parsing *data, t_cub *cub)
{
	char	**cub_map;
	int	i;
	
	cub_map = malloc(sizeof(char *) * (ft_arr_len(data->map) + 1));
	if (!cub_map)
		return (NULL);
	i = 0;
	while (data->map[i])
	{
		cub_map[i] = ft_strdup_sub(data->map[i], 'X', '1');
		if (!cub->map[i])
			return (ft_free_arr(cub_map), NULL);
		printf("%s\n", cub_map[i]);
		i++;
	}
	cub_map[i] = 0;
	return (cub_map);
}

int	map_parsing(t_cub *cub)
{
	t_parsing	data;

	data.file = cub->path;
	data.player_flag = 0;
	get_width(&data);
	printf("%d\n", data.width);
	if (get_checking_map(&data) != 0)
		return (ft_free_arr(data.map), 1);
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	if (check_map_limits(&data) != 0)
		return (ft_free_arr(data.map), 1);
	if (check_bad_char(&data) != 0)
		return (ft_free_arr(data.map), 1);
	if (check_map_player(&data) != 0)
		return (ft_free_arr(data.map), 1);
	printf("\033[32;01mGood !\033[00m\n");
	cub->map = set_cub_map(&data, cub);
	// i = 0;
	// while (cub->map[i])
	// {
	// 	printf("%s\n", cub->map[i]);
	// 	i++;
	// }
	return (ft_free_arr(data.map), 0);
}