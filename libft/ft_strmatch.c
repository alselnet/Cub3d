/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:32:55 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/23 16:21:01 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strmatch(const char *s, const char *charset)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isinbase(s[i], charset))
			return (1);
	}
	return (0);
}
