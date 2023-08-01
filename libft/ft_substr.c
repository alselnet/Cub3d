/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:52:02 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/11 13:53:40 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	substrlen(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < start && s[i])
		i++;
	while (j < len && s[i] && len)
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*substr;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	substr = (char *)malloc(substrlen(s, start, len) + 1);
	if (!substr)
		return (0);
	while (i < start && s[i])
		i++;
	while (j < len && s[i] && len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = 0;
	return (substr);
}
/*int main(void)
{
	char * s = ft_substr("tripouille", 100, 1);
	printf("string is : tripouille\n");
	printf("substring is : %s\n", s);
	free (s);

	s = ft_substr("BONJOUR LES HARICOTS !", 100, 1);
	printf("string is : BONJOUR LES HARICOTS !\n");
	printf("substring is : %s\n", s);
	free(s);
	return (0);
}*/