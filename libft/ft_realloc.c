/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:10:16 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 18:03:38 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	len;

	new_ptr = ft_calloc(sizeof(char), size);
	if (!new_ptr)
		return (0);
	len = ft_strlen((char *)ptr) + 1;
	if (len > size)
		len = size;
	ft_strlcpy(new_ptr, ptr, len);
	free(ptr);
	return (new_ptr);
}
