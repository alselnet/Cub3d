/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:48:58 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/11 13:57:42 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(len + 1);
	if (!join)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}
/*int	main()
{
	char*	join;
	int		i;

	i = 0;
	char string1[] = "hello guys ";
	char string2[] = "this is a test for join";
	join = ft_strjoin(string1, string2);
	printf("processing the following strings :\n%s\n%s\n\n", string1, string2);
	printf("ft_strjoin returns : %s\n", join);
	free(join);
	return (0);
}*/