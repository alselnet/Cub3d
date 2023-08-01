/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:59:05 by aselnet           #+#    #+#             */
/*   Updated: 2022/04/04 18:55:02 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	while ((i < n - 1) && (s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
/*int main()
{
    char string1[8] = "bonjour";
	char string2[8] = "bon";
	
	int result1 = ft_strncmp (string1, string2, 0);
	int result2 = strncmp (string1, string2, 0);
	printf("the result of ft_strncmp is %d\n", result1);
	printf("the result of strncmp is %d", result2);
    return (0);
}*/