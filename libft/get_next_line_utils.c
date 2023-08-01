/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:06:11 by aselnet           #+#    #+#             */
/*   Updated: 2023/04/05 20:36:19 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		*p = 0;
		p++;
		i++;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = (void *)malloc (count * size);
	if (!result)
		return (0);
	ft_bzero (result, count * size);
	return (result);
}

int	ft_chr_is_in_base(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*join;

	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(len + 1);
	if (!join)
		return (0);
	while (s1[++i])
		join[i] = s1[i];
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	if (s1)
		free (s1);
	return (join);
}
