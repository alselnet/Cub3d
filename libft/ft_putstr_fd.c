/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:48:31 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/24 13:51:15 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		write (fd, s + i, 1);
	return (i);
}
/*int	main()
{
	char s[] = "salut a tous les ptizamis";
	ft_putstr_fd(s, 2);
	return (0);
}*/