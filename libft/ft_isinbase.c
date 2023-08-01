/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:04 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/19 14:28:56 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinbase(int c, char const *set)
{
	int	i;

	i = 0;
	if (!set || !c)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/*int main()
{
    char    c;
	int	i;

    printf("Please enter a character :\n");
    scanf("%c", &c);
    i = ft_isalnum(c);
    printf("ft_isalnum returns %d\n", i);
    return (0);
}*/