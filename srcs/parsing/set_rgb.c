/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:35:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/08 20:51:33 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb(t_rgb *rgb)
{
	if (rgb->red)
		free(rgb->red);
	if (rgb->green)
		free(rgb->green);
	if (rgb->blue)
		free(rgb->blue);
}

int	ft_strlen_lim(char *str, char lim)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != lim)
		i++;
	return (i);
}

int	create_spaces(char *str, t_rgb *rgb)
{
	int r_len;
	int	g_len;
	int	b_len;

	r_len = ft_strlen_lim(str, ',');
	rgb->red = malloc(sizeof(char) * (r_len + 1));
	if (!rgb->red)
		return (1);
	g_len = ft_strlen_lim(str + r_len + 1, ',') ;
	rgb->green = malloc(sizeof(char) * (g_len + 1));
	if (!rgb->green)
		return (1);
	b_len = ft_strlen_lim(str + r_len + g_len + 2, ',');
	rgb->blue = malloc(sizeof(char) * (b_len + 1));
	if (!rgb->blue)
		return (1);
	return (0);
}

int	fill_rgb(char *str, char *dest, int *i)
{
	// int	j;

	// j = 0;
	// while (str[*i] && str[*i] != ',')
	// {
	// 	dest[j] = str[*i];
	// 	*i++;
	// }
	// dest[j] = 0;
	// ++*i;
	(void) str;
	(void) dest;
	(void) i;
	return (0);
}

int	set_rgb(char *str)
{
	t_rgb	rgb;
	int		i;
	int		j;

	(void) j;
	if (create_spaces(str, &rgb) != 0)
		return (free_rgb(&rgb), 1);
	i = 0;
	fill_rgb(str, rgb.red, &i);
	printf("%d\n", i);
	fill_rgb(str, rgb.green, &i);
	printf("%d\n", i);

	fill_rgb(str, rgb.blue, &i);
	printf("%d\n", i);
	return (0);
}
