/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:06:15 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 20:36:04 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_make_a_split(char const *s, size_t size)
{
	unsigned int	i;
	char			*split;

	i = 0;
	split = (char *) malloc(size + 1);
	if (!split)
		return (0);
	while (i < size)
	{
		split[i] = s[i];
		i++;
	}
	split[i] = 0;
	return (split);
}

int	ft_strslen(char const *s, int c)
{
	int	slen;
	int	i;
	int	j;

	slen = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		if (j)
			slen++;
	}
	return (slen);
}

char	**clear_tab(char **split_tab, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
		free(split_tab[n]);
	return (0);
}

char	**splitting(char **split_tab, char const *s, char c)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		n;

	i = 0;
	n = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		i += j;
		if (j)
		{
			split_tab[++n] = ft_make_a_split(s + i - j, j);
			if (!split_tab[n])
				return (clear_tab(split_tab, n));
		}
	}
	split_tab[++n] = 0;
	return (split_tab);
}

char	**ft_split(char const *s, char c)
{
	char				**split_tab;

	split_tab = (char **) malloc((ft_strslen(s, c) + 1) * sizeof(char *));
	if (!split_tab)
		return (0);
	split_tab = splitting(split_tab, s, c);
	return (split_tab);
}

/* #include <stdio.h>
int	main()
{
	char**	split_tab;
	int	i;

	i = 0;
	char string[] = "hey everyone im your new best split !!!\n";
	split_tab = ft_split(string, ' ');
	if (!split_tab)
		return (0);
	printf("ft_strslen returns: %d\n", ft_strslen(string, ' '));
	printf("processing the following string : %s\n", string);
	while (split_tab[i])
	{
		printf("%s\n", split_tab[i]);
		i++;
	}
	while (i >= 0)
	{
		free(split_tab[i]);
		i--;
	}
	free(split_tab);
	return (0);
} */