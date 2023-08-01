/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:16:08 by aselnet           #+#    #+#             */
/*   Updated: 2022/04/01 17:16:08 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lennum(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len ++;
	while (n)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			i;
	long long	nb;
	char		*number;

	i = 0;
	nb = n;
	if (n < 0)
		nb = -nb;
	number = malloc(ft_lennum(n) + 1);
	if (!number)
		return (0);
	while (nb)
	{
		number[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
		number[i] = '-';
	if (n == 0)
		number[i] = '0';
	number[ft_lennum(n)] = 0;
	ft_strrev(number);
	return (number);
}
/*int	main()
{
	int	n = -0;
	char *number;
	printf("number is %d\n", n);
	int len = ft_lennum(n);
	printf("lennum outputs : %d\n", len);
	number = ft_itoa(n);
	printf("ft_itoa outputs : %s\n", number);
	free (number);
	return (0);
}*/