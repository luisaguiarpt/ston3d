/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:16:44 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/10 14:14:22 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;
	char	*dest_cast;
	char	*src_cast;

	if (!src && !dest)
		return (NULL);
	src_cast = (char *)src;
	dest_cast = (char *)dest;
	i = 0;
	while (i < num)
	{
		dest_cast[i] = src_cast[i];
		i++;
	}
	return (dest);
}
