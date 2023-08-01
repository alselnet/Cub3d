/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:57 by aselnet           #+#    #+#             */
/*   Updated: 2022/04/04 19:15:29 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*int main()
{
    char src[8] = "bonjour";
	char dst[10] = "AAAAAAAAA";
	
	size_t result = ft_strlcpy(dst, src, 1);
	printf("the result of ft_strlcpy is %d\n", result);
	printf("the copy of ft_strlcpy is %c\n", dst[1]);
    return (0);
}*/