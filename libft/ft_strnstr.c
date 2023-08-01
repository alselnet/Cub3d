/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:59:09 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/06 18:30:42 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!little || !little[0])
		return ((char *)big);
	if (!big)
		return (0);
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && ((i + j) < len)
			&& little[j] && big[i + j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
/*int main()
{
	char big[30] = "aaabcabcd";
	char little[10] = "aabc";
	char *empty =(char*) "";
	char	*result1;

	result1 = ft_strnstr(empty, little, 0);
	printf("1 : ft_strnstr returns %s\n", result1);
	result1 = ft_strnstr(empty, little, -1);
	printf("2 : ft_strnstr returns %s\n", result1);
	result1 = ft_strnstr(empty, "c", -1);
	printf("4 : ft_strnstr returns %s\n", result1);
	result1 = ft_strnstr(empty, "", -1);
	printf("5 : ft_strnstr returns %s\n", result1);
	result1 = ft_strnstr(empty, little, 0);
	printf("6 : ft_strnstr returns %s\n", result1);
	result1 = ft_strnstr(empty, "coucou", -1);
	printf("7 : ft_strnstr returns %s\n", result1);
    return (0);
}*/
