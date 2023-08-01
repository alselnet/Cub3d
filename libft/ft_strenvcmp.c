/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strenvcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:21:39 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 16:42:06 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strenvcmp(const char *s1, char *env, size_t n)
{
	char	*cursor;
	size_t	i;

	i = 0;
	cursor = env;
	if (!n)
		return (0);
	while (*cursor && *cursor != '=')
	{
		cursor++;
		i++;
	}
	if (i < n)
		i = n;
	return (ft_strncmp(s1, env, i));
}
