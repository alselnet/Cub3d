/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:35:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/11 17:05:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int convert_rgb(int red, int green, int blue)
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

int	set_rgb(char *str)
{
	t_rgb	rgb;
	char	**arr;

	arr = ft_split(str, ',');
	rgb.red = ft_atoi(arr[0]);
	rgb.green = ft_atoi(arr[1]);
	rgb.blue = ft_atoi(arr[2]);
	rgb.color = convert_rgb(rgb.red, rgb.green, rgb.blue);
	ft_free_arr(arr);
	return (rgb.color);
}
