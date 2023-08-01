/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:49 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/06 18:27:25 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	dst = (char *) malloc(ft_strlen(s) + 1);
	if (!dst)
		return (0);
	ft_bzero(dst, ft_strlen(s) + 1);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}
/*int main()
{
    char string[50] = "hey guyzzzzz";
	char *dup1 = ft_strdup(string);
	printf("the result of ft_strdup is %s\n", dup1);
	char *dup2 = strdup(string);
	printf("the result of strdup is %s\n", dup2);
	free(dup1);
	free(dup2);
    return (0);
}*/