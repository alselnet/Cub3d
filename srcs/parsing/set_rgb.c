/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:35:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 18:38:58 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb(int red, int green, int blue)
{
	int	color;

	if (red < 0 || red > 255)
		return (-1);
	if (green < 0 || green > 255)
		return (-1);
	if (blue < 0 || blue > 255)
		return (-1);
	color = (red << 16) | (green << 8) | blue;
	return (color);
}

int	check_rgb(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != ',')
			return (1);
		if (str[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (1);
	return (0);
}

int	set_rgb(char *str)
{
	t_rgb	rgb;
	char	**arr;

	if (check_rgb(str) != 0)
	{
		printf("\033[31;01mInfos error : \033[00m");
		printf("Invalid character in RGB value !\n");
		return (-1);
	}
	arr = ft_split(str, ',');
	if (ft_arr_len(arr) != 3)
	{
		printf("\033[31;01mInfos error :\033[00m Invalid RGB value !\n");
		return (ft_free_arr(arr), -1);
	}
	rgb.red = ft_atoi(arr[0]);
	rgb.green = ft_atoi(arr[1]);
	rgb.blue = ft_atoi(arr[2]);
	rgb.color = convert_rgb(rgb.red, rgb.green, rgb.blue);
	if (rgb.color < 0)
		printf("\033[31;01mInfos error :\033[00m Invalid RGB value !\n");
	ft_free_arr(arr);
	return (rgb.color);
}
