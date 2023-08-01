/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:52:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/08/01 22:38:27 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	int	*arr;

	if (size && n > (size_t) - 1 / size)
		return (0);
	arr = (void *)malloc(n * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, n * size);
	return (arr);
}
