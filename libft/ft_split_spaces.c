/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:53:41 by jthuysba          #+#    #+#             */
/*   Updated: 2023/09/12 17:57:47 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			count++;
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	count_char(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

static void	copy_words(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] && !ft_isspace(src[i]))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_split_spaces(char const *s)
{
	size_t	i;
	size_t	x;
	char	**arr;

	i = 0;
	x = 0;
	arr = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		else
		{
			arr[x] = malloc(sizeof(char) * (count_char(s + i) + 1));
			if (!arr[x])
				return (NULL);
			copy_words(arr[x++], s + i);
			i += count_char(s + i);
		}
	}
	arr[x] = 0;
	return (arr);
}
