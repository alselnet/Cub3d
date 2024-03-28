/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:10:54 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/01 22:36:53 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;
	size_t	d;

	i = 0;
	j = 0;
	d = ft_strlen(dest);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (d + ft_strlen(src));
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		dest[j] = s2[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (free(s1), dest);
}
