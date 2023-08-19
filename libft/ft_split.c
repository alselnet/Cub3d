/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:06:15 by aselnet           #+#    #+#             */
/*   Updated: 2023/08/19 20:09:14 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char sep)
{
	size_t	i;
	size_t	k;
	size_t	words;

	i = 0;
	k = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != sep && k == 0)
		{
			k = 1;
			words++;
		}
		if (s[i] == sep)
			k = 0;
		i++;
	}
	return (words);
}

static size_t	count_char(char const *s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i] != sep && s[i])
		i++;
	return (i);
}

static void	copy_words(char *dest, const char *src, char sep)
{
	size_t	i;

	i = 0;
	while (src[i] != sep && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_split(char const *s, char sep)
{
	size_t	i;
	size_t	x;
	char	**arr;

	i = 0;
	x = 0;
	arr = malloc(sizeof(char *) * (count_words(s, sep) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (s[i] == sep)
			i++;
		else
		{
			arr[x] = malloc(sizeof(char) * (count_char(s + i, sep) + 1));
			if (!arr[x])
				return (NULL);
			copy_words(arr[x++], s + i, sep);
			i += count_char(s + i, sep);
		}
	}
	arr[x] = 0;
	return (arr);
}
